#include "searchbar.h"

SearchBar::SearchBar(QWidget *parent)
    :QToolBar(parent)
{

    mEdit = new QLineEdit;
    addAction(qApp->style()->standardIcon(QStyle::SP_TitleBarCloseButton),"",[this](){activate(false);});
    addWidget(mEdit);
    QAction * prevAction = addAction("previous");
    QAction * nextAction = addAction("next");

    nextAction->setShortcut(QKeySequence::FindNext);
    prevAction->setShortcut(QKeySequence::FindPrevious);
    nextAction->setToolTip(QString(tr("Next (%1)")).arg(nextAction->shortcut().toString()));
    prevAction->setToolTip(QString(tr("Previous (%1)")).arg(prevAction->shortcut().toString()));


    connect(prevAction,SIGNAL(triggered(bool)),this,SIGNAL(previousPressed()));
    connect(nextAction,SIGNAL(triggered(bool)),this,SIGNAL(nextPressed()));
    connect(mEdit,SIGNAL(textChanged(QString)), this, SIGNAL(textChanged(QString)));


    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);



}

void SearchBar::activate(bool visible)
{
    setVisible(visible);

    if (visible)
        mEdit->setFocus();

    if (mSearchAction)
        mSearchAction->setChecked(visible);
}

QAction *SearchBar::createSearchAction(const QString &name)
{
    mSearchAction= new QAction(name);
    mSearchAction->setCheckable(true);
    mSearchAction->setChecked(true);
    mSearchAction->setShortcut(QKeySequence::Find);
    connect(mSearchAction, &QAction::triggered, this, &SearchBar::activate);

    return mSearchAction;
}

QString SearchBar::text() const
{
    return mEdit->text();
}



