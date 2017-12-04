#ifndef ABSTRACTPANELWIDGET_H
#define ABSTRACTPANELWIDGET_H
#include <QtWidgets>
#include "abstractsequencetrace.h"

class AbstractPanelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractPanelWidget(QWidget *parent = 0);
    void setTrace(AbstractSequenceTrace * trace);
    void setCentralWidget(QWidget * widget);

    AbstractSequenceTrace * trace();

    virtual void load() = 0;


private:
    AbstractSequenceTrace * mTrace;
    QWidget * mCentralWidget = nullptr;
};

#endif // ABSTRACTPANELWIDGET_H
