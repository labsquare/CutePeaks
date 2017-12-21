#include "cuttracecommand.h"


CutTraceCommand::CutTraceCommand(TraceView * view, int pos, int length)
    :QUndoCommand(), mView(view), mPos(pos), mLength(length)
{

   setText(QStringLiteral("Remove [%1:%2]").arg(mPos).arg(mPos+mLength));
}

void CutTraceCommand::redo()
{
    mCutTrace = mView->cutTrace(mPos, mLength);
}

void CutTraceCommand::undo()
{
    mView->pasteTrace(mCutTrace);
}

