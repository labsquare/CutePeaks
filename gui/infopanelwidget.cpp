#include "infopanelwidget.h"

InfoPanelWidget::InfoPanelWidget(QWidget *parent)
    :AbstractPanelWidget(parent)
{

    mView  = new QTableView;
    mModel = new QStandardItemModel;
    mModel->setColumnCount(2);
    setCentralWidget(mView);

    mView->setSelectionBehavior(QAbstractItemView::SelectRows);
    mView->setSelectionMode(QAbstractItemView::SingleSelection);
    mView->verticalHeader()->hide();
    mView->setAlternatingRowColors(true);
    mView->setModel(mModel);

    setWindowTitle("Information");


}

void InfoPanelWidget::load()
{
    mModel->clear();

    for (QString key : trace()->keys())
    {
        QList<QStandardItem*> row;
        QStandardItem * keyItem = new QStandardItem();
        QStandardItem * valItem = new QStandardItem();

        keyItem->setText(key);
        valItem->setText(trace()->value(key).toString());

        row << keyItem << valItem;
        mModel->appendRow(row);
    }

    mModel->setHorizontalHeaderLabels({"Key","Value"});

    mView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    mView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);


}
