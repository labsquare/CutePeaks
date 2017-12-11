#ifndef INFOVIEW_H
#define INFOVIEW_H
#include <QtWidgets>
#include <QStandardItemModel>
#include "abstractpanelwidget.h"

class InfoPanelWidget : public AbstractPanelWidget
{
public:
    InfoPanelWidget(QWidget * parent = 0);
    void load() override;



private:
    QStandardItemModel * mModel;
    QTableView * mView;
};

#endif // INFOVIEW_H
