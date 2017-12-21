#include "searchbar.h"

SearchBar::SearchBar(QWidget *parent)
    :QToolBar(parent)
{

        mEdit = new QLineEdit;
        addAction(qApp->style()->standardIcon(QStyle::SP_TitleBarCloseButton),"",[this](){activate(false);});
        addWidget(mEdit);

        addAction("Find Previous", this, SLOT(previous()))->setShortcut(QKeySequence::FindNext);
        addAction("Find Next", this, SLOT(next()))->setShortcut(QKeySequence::FindPrevious);

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

void SearchBar::next()
{

}

void SearchBar::previous()
{

}

