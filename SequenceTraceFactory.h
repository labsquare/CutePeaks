#ifndef SEQUENCETRACEFACTORY_H
#define SEQUENCETRACEFACTORY_H
#include <QtCore>

class SequenceTraceFactory
{
public:
    enum FileType{
        UnknownType,
        ZTRType,
        ABIFType,
        SCFType
    };

    static FileType filetype(QIODevice * device);
    static FileType filetype(const QString& filename);




private:
    SequenceTraceFactory();
};

#endif // SEQUENCETRACEFACTORY_H
