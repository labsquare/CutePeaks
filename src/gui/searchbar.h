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

    QString text() const;



Q_SIGNALS:
    void nextPressed();
    void previousPressed();
    void textChanged(const QString& text);



private:
    QLineEdit * mEdit;
    QAction * mSearchAction = nullptr;

};

#endif // SEARCHBAR_H
