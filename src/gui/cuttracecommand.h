#ifndef CUTTRACECOMMAND_H
#define CUTTRACECOMMAND_H
#include <QUndoCommand>
#include "mainwindow.h"
#include "trace.h"

class MainWindow;
class CutTraceCommand : public QUndoCommand
{
public:
    CutTraceCommand(MainWindow * main, int pos, int length);

    virtual void redo() override;
    virtual void undo() override;


private:
    MainWindow * mMain = nullptr;
    Trace * mCutTrace = nullptr;
    int mPos;
    int mLength;
};

#endif // CUTTRACECOMMAND_H
