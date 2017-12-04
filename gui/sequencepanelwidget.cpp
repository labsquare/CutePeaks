#include "sequencepanelwidget.h"

SequencePanelWidget::SequencePanelWidget(QWidget * parent)
    :AbstractPanelWidget(parent)
{
    mEdit = new QPlainTextEdit;
    mHighlighter = new SequenceHighlighter(mEdit->document());
    setCentralWidget(mEdit);

    setWindowTitle(tr("Sequence"));

    connect(mEdit,SIGNAL(selectionChanged()),this,SLOT(test()));


}

void SequencePanelWidget::load()
{

    mEdit->setPlainText(trace()->sequence().byteArray());

}

void SequencePanelWidget::test()
{


    qDebug()<<"change";

}
