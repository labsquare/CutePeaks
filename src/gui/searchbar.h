#ifndef SEARCHBAR_H
#define SEARCHBAR_H
#include <QtWidgets>

class SearchBar : public QToolBar
{
    Q_OBJECT
public:
    SearchBar(QWidget * parent = nullptr);
    void activate(bool visible);
    QAction * createSearchAction(const QString& name = QString());

public Q_SLOTS:
    void next();
    void previous();



private:
    QLineEdit * mEdit;
    QAction * mSearchAction = nullptr;

};

#endif // SEARCHBAR_H
