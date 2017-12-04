#ifndef SEQUENCEEDITOR_H
#define SEQUENCEEDITOR_H
#include <QtWidgets>
#include "abstractpanelwidget.h"
#include "sequencehighlighter.h"

class SequencePanelWidget : public AbstractPanelWidget
{
public:
    SequencePanelWidget(QWidget * parent = 0);
    void load();


public Q_SLOTS:
    void test();

private:
    QPlainTextEdit * mEdit;
    SequenceHighlighter * mHighlighter;
};

#endif // SEQUENCEEDITOR_H
