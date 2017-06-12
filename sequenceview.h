#ifndef SEQUENCEVIEW_H
#define SEQUENCEVIEW_H
#include <QtWidgets>
#include "sequence.h"

class SequenceView : public QTextEdit
{
public:
    SequenceView(QWidget * parent = 0);
    void setSequence(const Sequence& sequence);



private:
    Sequence mSequence;

};

#endif // SEQUENCEVIEW_H
