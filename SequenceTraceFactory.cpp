#include "SequenceTraceFactory.h"


SequenceTraceFactory::FileType SequenceTraceFactory::filetype(QIODevice *device)
{

    if (device->open(QIODevice::ReadOnly))
    {
        QByteArray magic = device->read(8);

        if (magic.left(4) == "ABIF")
            return ABIFType;

        device->close();
    }

    return UnknownType;

}

SequenceTraceFactory::FileType SequenceTraceFactory::filetype(const QString &filename)
{
    QFile file(filename);
    return SequenceTraceFactory::filetype(&file);
}

SequenceTraceFactory::SequenceTraceFactory()
{

}
