#include "sequenceview.h"

SequenceView::SequenceView(QWidget * parent)
    :QPlainTextEdit(parent)
{
    mHighlighter = new SequenceHighlighter(document());

    setReadOnly(true);
    connect(this, &SequenceView::blockCountChanged, this, &SequenceView::updateFoo);

    setWindowTitle(tr("Sequences"));

    setViewportMargins(20,0,0,0);

}

void SequenceView::setSequence(const Sequence &sequence)
{
    mSequence = sequence;
    setPlainText(sequence.byteArray());
}

void SequenceView::resizeEvent(QResizeEvent *event)
{
    // display h
    qDebug()<<document()->documentLayout()->documentSize();

    QPlainTextEdit::resizeEvent(event);
}



void SequenceView::updateFoo(int v)
{
    qDebug()<<v;
}

