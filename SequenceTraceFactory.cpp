#include "SequenceTraceFactory.h"


SequenceTraceFactory::FileType SequenceTraceFactory::filetype(QIODevice *device)
{

    if (device->open(QIODevice::ReadOnly))
    {
        QByteArray magic = device->read(8);

        if (magic.left(4) == "ABIF")
            return ABIF;

        device->close();
    }

    return Unknown;

}

SequenceTraceFactory::FileType SequenceTraceFactory::filetype(const QString &filename)
{
    QFile file(filename);
    return SequenceTraceFactory::filetype(&file);
}

AbstractSequenceTrace *SequenceTraceFactory::loadTraceFile(const QString &filename)
{

    QFile * file = new QFile(filename);

    if (SequenceTraceFactory::filetype(filename) == ABIF)
        return new AbifSequenceTrace(file);

    delete file;
    return nullptr;

}

SequenceTraceFactory::SequenceTraceFactory()
{

}
