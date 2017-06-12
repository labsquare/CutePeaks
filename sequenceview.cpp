#include "sequenceview.h"

SequenceView::SequenceView(QWidget * parent)
    :QTextEdit(parent)
{

    setReadOnly(true);

}

void SequenceView::setSequence(const Sequence &sequence)
{
    mSequence = sequence;
    setText(sequence.byteArray());
}

