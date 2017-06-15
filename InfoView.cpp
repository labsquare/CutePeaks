#include "InfoView.h"

InfoView::InfoView(QWidget *parent)
    :QTableView(parent)
{

    mModel = new QStandardItemModel;
    mModel->setColumnCount(2);



    setModel(mModel);

}

void InfoView::setTrace(AbstractSequenceTrace *trace)
{
    mModel->clear();

    for (QString key : trace->keys())
    {
        QList<QStandardItem*> row;
        QStandardItem * keyItem = new QStandardItem();
        QStandardItem * valItem = new QStandardItem();

        keyItem->setText(key);
        valItem->setText(trace->value(key).toString());

        row << keyItem << valItem;
        mModel->appendRow(row);


    }


}
