#ifndef ABSTRACTPANELWIDGET_H
#define ABSTRACTPANELWIDGET_H
#include <QtWidgets>
#include "abstracttracereader.h"
#include "trace.h"

class AbstractPanelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractPanelWidget(QWidget *parent = 0);
    void setTrace(const Trace * trace);
    void setCentralWidget(QWidget * widget);

    const Trace * trace() const;

    virtual void load() = 0;


private:
    const Trace * mTrace;
    QWidget * mCentralWidget = nullptr;
};

#endif // ABSTRACTPANELWIDGET_H
