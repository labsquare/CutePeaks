#ifndef SEQUENCEVIEW_H
#define SEQUENCEVIEW_H
#include <QtWidgets>
#include "sequence.h"

class SequenceView : public QPlainTextEdit
{
    Q_OBJECT
public:
    SequenceView(QWidget * parent = 0);
    void setSequence(const Sequence& sequence);

protected:
    void resizeEvent(QResizeEvent * event);

protected Q_SLOTS:
    void updateFoo(int v);



private:
    Sequence mSequence;

};

#endif // SEQUENCEVIEW_H
