#ifndef SEQUENCEEDITOR_H
#define SEQUENCEEDITOR_H
#include <QtWidgets>
#include "abstractpanelwidget.h"
#include "sequencehighlighter.h"


class SequencePanelWidget : public AbstractPanelWidget
{
    Q_OBJECT
public:
    SequencePanelWidget(QWidget * parent = 0);
    void load();

    void setText(const QString& text);



public Q_SLOTS:
    void test();

Q_SIGNALS:
    void selectionChanged(int pos, int length);

private:
    QPlainTextEdit * mEdit;
    SequenceHighlighter * mHighlighter;
};

#endif // SEQUENCEEDITOR_H
