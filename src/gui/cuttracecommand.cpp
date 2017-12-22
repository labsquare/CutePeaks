#include "cuttracecommand.h"

CutTraceCommand::CutTraceCommand(MainWindow * main, int pos, int length)
    :QUndoCommand(), mMain(main), mPos(pos), mLength(length)
{

   setText(QStringLiteral("Remove [%1:%2]").arg(mPos).arg(mPos+mLength));
}

void CutTraceCommand::redo()
{
    mCutTrace = mMain->view()->cutTrace(mPos, mLength);
    mMain->panel()->setText(mMain->view()->trace()->sequence().toString());
}

void CutTraceCommand::undo()
{
    mMain->view()->pasteTrace(mCutTrace);
    mMain->panel()->setText(mMain->view()->trace()->sequence().toString());

}

