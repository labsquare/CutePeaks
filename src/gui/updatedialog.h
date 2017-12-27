#ifndef UPDATEWIDGET_H
#define UPDATEWIDGET_H
#include <QtWidgets>
#include <QtNetwork>
#include <QJsonDocument>
#include <QDesktopServices>
class UpdateDialog : public QDialog
{
    Q_OBJECT
public:
    UpdateDialog(QWidget * parent = nullptr);

    void check();

protected Q_SLOTS:
    void parse();
    void openUrl();



private:
    QLabel * mLabel;

    QNetworkAccessManager * mManager;
    QPushButton * mDLButton;
    QUrl mDLUrl;

};

#endif // UPDATEWIDGET_H
