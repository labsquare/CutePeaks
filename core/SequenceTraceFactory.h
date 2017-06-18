#ifndef SEQUENCETRACEFACTORY_H
#define SEQUENCETRACEFACTORY_H
#include <QtCore>
#include "AbifSequenceTrace.h"
#include "ScfSequenceTrace.h"

class SequenceTraceFactory
{
public:
    enum FileType{
        Unknown,
        ZTR,
        ABIF,
        SCF
    };

    static FileType filetype(QIODevice * device);
    static FileType filetype(const QString& filename);

    static AbstractSequenceTrace * loadTraceFile(const QString& filename);




private:
    SequenceTraceFactory();
};

#endif // SEQUENCETRACEFACTORY_H
