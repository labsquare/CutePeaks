#include "ScfSequenceTrace.h"

ScfSequenceTrace::ScfSequenceTrace(QIODevice * device)
    :AbstractSequenceTrace(device)
{
    load();
}
//-------------------------------------------------------------------

const QHash<QChar, QVector<int>>&ScfSequenceTrace::traces() const
{
    return mTraces;
}
//-------------------------------------------------------------------

const QByteArray& ScfSequenceTrace::sequence() const
{
    return mBaseCalls;
}
//-------------------------------------------------------------------

const QVector<int>& ScfSequenceTrace::baseLocations() const
{
    return mBaseLocations;
}
//-------------------------------------------------------------------

const QVector<int>& ScfSequenceTrace::confScores() const
{
    return mConfScores;
}
//-------------------------------------------------------------------

bool ScfSequenceTrace::load()
{
    // See specification
    // http://staden.sourceforge.net/scf-rfc.html

    if (device()->open(QIODevice::ReadOnly))
    {
         readHeader();

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

void ScfSequenceTrace::readHeader()
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
void ScfSequenceTrace::readTraces()
{
    mTraces.clear();
    device()->reset();
    QDataStream stream(device());
    device()->seek(mHeader.samples_offset);
    for (QChar base : {'A','C','G','T'})
    {
        QVector<T> data;
        for (int i=0; i<mHeader.samples; ++i)
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
void ScfSequenceTrace::decodeDelta(QVector<T>& data)
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
QByteArray ScfSequenceTrace::version() const
{
    return QByteArray::fromRawData(mHeader.version,4);
}



