#include "sequencepanelwidget.h"

SequencePanelWidget::SequencePanelWidget(QWidget * parent)
    :AbstractPanelWidget(parent)
{
    mEdit = new QPlainTextEdit;
    setCentralWidget(mEdit);

    setWindowTitle(tr("Sequence"));


}

void SequencePanelWidget::load()
{

    mEdit->setPlainText(trace()->sequence().byteArray());

}
