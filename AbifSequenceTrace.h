#ifndef ABIFSEQUENCETRACE_H
#define ABIFSEQUENCETRACE_H
#include "AbstractSequenceTrace.h"

class AbifSequenceTrace : public AbstractSequenceTrace
{
public:
    AbifSequenceTrace(QIODevice * device);
};

#endif // ABIFSEQUENCETRACE_H
