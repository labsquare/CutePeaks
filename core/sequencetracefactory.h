#ifndef SEQUENCETRACEFACTORY_H
#define SEQUENCETRACEFACTORY_H
#include <QtCore>
#include "abifsequencetrace.h"
#include "scfsequencetrace.h"
#include "trace.h"

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

    static Trace loadTraceFile(const QString& filename);




private:
    SequenceTraceFactory();
};

#endif // SEQUENCETRACEFACTORY_H
