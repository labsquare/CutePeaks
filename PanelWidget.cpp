#include "PanelWidget.h"

PanelWidget::PanelWidget(QWidget * parent)
    :QTabWidget(parent)
{

}

void PanelWidget::addPanel(QWidget *panel)
{
    addTab(panel, panel->windowIcon(), panel->windowTitle());
}
