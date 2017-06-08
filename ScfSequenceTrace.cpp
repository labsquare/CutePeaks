#include "ScfSequenceTrace.h"

ScfSequenceTrace::ScfSequenceTrace(QIODevice * device)
    :AbstractSequenceTrace(device)
{
    load();
}

const QHash<QChar, QVector<int>>&ScfSequenceTrace::traces() const
{
   return mTraces;
}
const QByteArray& ScfSequenceTrace::sequence() const
{
    return mBaseCalls;
}
const QVector<int>& ScfSequenceTrace::baseLocations() const
{
    return mBaseLocations;
}
const QVector<int>& ScfSequenceTrace::confScores() const
{
    return mConfScores;
}

bool ScfSequenceTrace::load()
{
    if (device()->open(QIODevice::ReadOnly))
    {
        QDataStream stream(device());
        // Read Header
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

        // Read Trace
        device()->reset();
        device()->seek(mHeader.samples_offset);
        qDebug()<<"sample size" << mHeader.sample_size;
        qDebug()<<"sample " << mHeader.samples;

        for (QChar base : {'A','C','G','T'})
        {
            // reads A
            for (int i=0; i<mHeader.samples; ++i)
            {
                quint8 value;
                stream >> value;
                //qDebug()<<value;

            }
        }




        return true;
    }

    return false;
}

QByteArray ScfSequenceTrace::version() const
{
    return QByteArray::fromRawData(mHeader.version,4);
}
