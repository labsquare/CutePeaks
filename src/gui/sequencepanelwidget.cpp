#include "sequencepanelwidget.h"

SequencePanelWidget::SequencePanelWidget(QWidget * parent)
    :AbstractPanelWidget(parent)
{
    mEdit = new FastaEditor;
    mHighlighter = new SequenceHighlighter(mEdit->document());
    setCentralWidget(mEdit);

    setWindowTitle(tr("Sequence"));

    connect(mEdit,SIGNAL(selectionChanged()),this,SLOT(test()));

    mEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
}

void SequencePanelWidget::load()
{

    mEdit->setPlainText(trace()->sequence().byteArray());

}

void SequencePanelWidget::test()
{
    int pos = mEdit->textCursor().selectionStart();
    int length = mEdit->textCursor().selectionEnd() - mEdit->textCursor().selectionStart();
    emit selectionChanged(pos, length);

}


