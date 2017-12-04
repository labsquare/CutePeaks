#include "abstractpanelwidget.h"

AbstractPanelWidget::AbstractPanelWidget(QWidget *parent) : QWidget(parent)
{

}

void AbstractPanelWidget::setTrace(Trace *trace)
{
    mTrace = trace;
    load();


}

void AbstractPanelWidget::setCentralWidget(QWidget *widget)
{
    if (mCentralWidget == nullptr)
    {
        mCentralWidget = widget;
        QVBoxLayout * centralLayout = new QVBoxLayout;
        centralLayout->addWidget(mCentralWidget);
        centralLayout->setContentsMargins(0,0,0,0);
        setLayout(centralLayout);
    }


}

Trace *AbstractPanelWidget::trace()
{
    return mTrace;
}
