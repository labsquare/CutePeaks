#ifndef SEQUENCEEDITOR_H
#define SEQUENCEEDITOR_H
#include <QtWidgets>
#include "abstractpanelwidget.h"

class SequencePanelWidget : public AbstractPanelWidget
{
public:
    SequencePanelWidget(QWidget * parent = 0);
    void load();

private:
    QPlainTextEdit * mEdit;
};

#endif // SEQUENCEEDITOR_H
