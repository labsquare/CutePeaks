#include "searchbar.h"
#include "qfonticon.h"
SearchBar::SearchBar(QWidget *parent)
    :QToolBar(parent)
{

    mEdit = new QLineEdit;
    addAction(qApp->style()->standardIcon(QStyle::SP_TitleBarCloseButton),"",[this](){hide();});
    addWidget(mEdit);
    QAction * prevAction = addAction(FIcon(0xf104), "previous");
    QAction * nextAction = addAction(FIcon(0xf105),"next");

    nextAction->setShortcut(QKeySequence::FindNext);
    prevAction->setShortcut(QKeySequence::FindPrevious);
    nextAction->setToolTip(QString(tr("Next (%1)")).arg(nextAction->shortcut().toString()));
    prevAction->setToolTip(QString(tr("Previous (%1)")).arg(prevAction->shortcut().toString()));

    widgetForAction(nextAction)->setLayoutDirection(Qt::RightToLeft);

    connect(prevAction,SIGNAL(triggered(bool)),this,SIGNAL(previousPressed()));
    connect(nextAction,SIGNAL(triggered(bool)),this,SIGNAL(nextPressed()));
    connect(mEdit,SIGNAL(textChanged(QString)), this, SIGNAL(textChanged(QString)));


    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);

    mEdit->setPlaceholderText("Search pattern ...");

    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);




}

void SearchBar::activate()
{
    qDebug()<<"activate";

    setVisible(!isVisible());

    if (isVisible())
        mEdit->setFocus();


}

QAction *SearchBar::createSearchAction(const QString &name)
{
    mSearchAction= new QAction(name);
    connect(mSearchAction, &QAction::triggered, this, &SearchBar::activate);

    return mSearchAction;
}

QString SearchBar::text() const
{
    return mEdit->text();
}

void SearchBar::setMatchCount(int count)
{
    QPalette pal = mEdit->palette();

    if ( count == 0)
     pal.setColor(QPalette::Text, Qt::red);
    else
        pal.setColor(QPalette::Text, palette().color(QPalette::Text));

    mEdit->setPalette(pal);

}



