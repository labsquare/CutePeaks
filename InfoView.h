#ifndef INFOVIEW_H
#define INFOVIEW_H
#include <QtWidgets>
#include <QStandardItemModel>
#include "AbstractSequenceTrace.h"

class InfoView : public QTableView
{
public:
    InfoView(QWidget * parent = 0);

    void setTrace(AbstractSequenceTrace * trace);


private:
    QStandardItemModel * mModel;
};

#endif // INFOVIEW_H
