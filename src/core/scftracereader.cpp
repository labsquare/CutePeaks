#include "scftracereader.h"
#include <iostream>
ScfTraceReader::ScfTraceReader(QIODevice * device)
    :AbstractTraceReader(device)
{
    load();
}
//-------------------------------------------------------------------

const QHash<QChar, QVector<int>>&ScfTraceReader::readDatas() const
{
    return mTraces;
}
//-------------------------------------------------------------------

const Sequence& ScfTraceReader::readSequence() const
{
    return mBaseCalls;

}
//-------------------------------------------------------------------

const QVector<int>& ScfTraceReader::readBaseLocations() const
{
    return mBaseLocations;
}
//-------------------------------------------------------------------

const QVector<int>& ScfTraceReader::readBaseScores() const
{
    return mConfScores;
}
//-------------------------------------------------------------------
const QHash<QString, QVariant> &ScfTraceReader::readMetadatas() const
{
    return mMetadatas;
}
//-------------------------------------------------------------------

bool ScfTraceReader::load()
{
    // See specification
    // http://staden.sourceforge.net/scf-rfc.html

    if (device()->open(QIODevice::ReadOnly))
    {
        readHeader();
        readMetadatas();
        readBases();

        // Traces can be encoded as 1 bytes or 2 bytes
        if (mHeader.sample_size == 1)
            readTraces<quint8>();

        if (mHeader.sample_size == 2)
            readTraces<quint16>();

        device()->close();
        return true;
    }

    return false;
}
void ScfTraceReader::readBases()
{
    // Reads base location
    mBaseLocations.clear();
    device()->reset();
    device()->seek(mHeader.bases_offset);
    QDataStream stream(device());
    for (quint32 i=0; i< mHeader.bases; ++i)
    {
        quint32 pos;
        stream >> pos;
        mBaseLocations.append(pos);
    }

    // Reads probability
    for (QChar base : {'A','C','G','T'} )
    {
        for (quint32 i=0; i< mHeader.bases; ++i)
        {
            quint8 pos;
            stream >> pos;
            mTempProba[base].append(pos);
        }
    }
    // Reads bases
    mBaseCalls = Sequence(device()->read(mHeader.bases), Sequence::Forward, Sequence::Dna);

    // build the confidence scores list
    mConfScores.clear();
    for (quint32 i=0; i< mHeader.bases; ++i)
    {
        QChar base = mBaseCalls.at(i);
        mConfScores.append(mTempProba[base].value(i));
    }
}
//-------------------------------------------------------------------
void ScfTraceReader::readMetadatas()
{
    mMetadatas.clear();
    device()->reset();
    device()->seek(mHeader.comments_offset);
    quint32 total = 0;
    while (total < mHeader.comments_size-1)
    {
        QByteArray line;
        line = device()->readLine();
        QList<QByteArray> rows = line.split('=');
        if (rows.size() == 2)
            mMetadatas.insert(rows[0],rows[1].simplified());
        total += line.length();
    }
}
//-------------------------------------------------------------------
void ScfTraceReader::readHeader()
{
    // Read Header
    device()->reset();
    QDataStream stream(device());
    stream >>mHeader.magic_number;
    stream >>mHeader.samples;
    stream >>mHeader.samples_offset;
    stream >>mHeader.bases;
    stream >>mHeader.bases_left_clip;
    stream >>mHeader.bases_right_clip;
    stream >>mHeader.bases_offset;
    stream >>mHeader.comments_size;
    stream >>mHeader.comments_offset;
    stream.readRawData((char*)mHeader.version, 4);
    stream >>mHeader.sample_size;
    stream >>mHeader.code_set;
    stream >>mHeader.private_size;
    stream >>mHeader.private_offset;
    stream.readRawData((char*)mHeader.spare, 18);





}
//-------------------------------------------------------------------
template <typename T>
void ScfTraceReader::readTraces()
{
    mTraces.clear();
    device()->reset();
    QDataStream stream(device());
    device()->seek(mHeader.samples_offset);
    for (QChar base : {'A','C','G','T'})
    {
        QVector<T> data;

        for (quint32 i=0; i<mHeader.samples; ++i)
        {
            T value;
            stream >> value;
            data.append(value);
        }
        // convert on place
        decodeDelta<T>(data);

        // add values in trace hash
        for (int i : data)
            mTraces[base].append(i);
    }
}
//-------------------------------------------------------------------
template<typename T>
void ScfTraceReader::decodeDelta(QVector<T>& data)
{

    //std::numeric_limits<T>::max();
    // this function returns the max value for the T int value.
    // Copy paste from seqtrace.. Don't understand
    for (int i=0; i<2 ; ++i)
    {
        int prev = 0;
        for (int cnt =0; cnt< data.length(); ++cnt)
        {
            int actual = data[cnt] + prev;
            if (actual > std::numeric_limits<T>::max())
                actual -=std::numeric_limits<T>::max() + 1;
            prev = actual;
            data[cnt] = actual;
        }
    }
}
//-------------------------------------------------------------------
QByteArray ScfTraceReader::version() const
{
    return QByteArray::fromRawData(mHeader.version,4);
}



