#ifndef CUTTRACECOMMAND_H
#define CUTTRACECOMMAND_H
#include <QUndoCommand>
#include "traceview.h"

class TraceView;
class CutTraceCommand : public QUndoCommand
{
public:
    CutTraceCommand(TraceView * view, int pos, int length);

    virtual void redo() override;
    virtual void undo() override;


private:
    TraceView * mView = nullptr;
    Trace * mCutTrace = nullptr;
    int mPos;
    int mLength;
};

#endif // CUTTRACECOMMAND_H
