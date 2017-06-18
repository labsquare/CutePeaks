#include "sequenceview.h"

SequenceView::SequenceView(QWidget * parent)
    :QPlainTextEdit(parent)
{

    setReadOnly(true);
    connect(this, &SequenceView::blockCountChanged, this, &SequenceView::updateFoo);

    setWindowTitle("Sequence");

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

