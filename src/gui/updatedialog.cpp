#include "updatedialog.h"
#include <QVersionNumber>
UpdateDialog::UpdateDialog(QWidget */*parent*/)
{

    mLabel   = new QLabel;
    mManager = new QNetworkAccessManager;

    auto buttons = new QDialogButtonBox(QDialogButtonBox::Ok);
    mDLButton = buttons->addButton(tr("Download"),QDialogButtonBox::ActionRole);
    mDLButton->setVisible(false);
    connect(mDLButton, &QPushButton::clicked, this, &UpdateDialog::openUrl);
    connect(buttons, &QDialogButtonBox::accepted, this, &UpdateDialog::close);

    mLabel->setAlignment(Qt::AlignCenter|Qt::AlignVCenter);
    mLabel->setText(tr("check updated ..."));

    auto mainLayout = new QVBoxLayout;

    mainLayout->addWidget(mLabel);
    mainLayout->addWidget(buttons);

    setLayout(mainLayout);
    setWindowTitle(tr("Updater"));

    check();
}

void UpdateDialog::check()
{
    QNetworkReply * reply = mManager->get(QNetworkRequest(QUrl("https://api.github.com/repos/labsquare/cutepeaks/releases/latest")));
    connect(reply,&QNetworkReply::finished, this, &UpdateDialog::parse);
}

void UpdateDialog::parse()
{

    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

    QVersionNumber lastVersion  = QVersionNumber::fromString(doc.object().value("tag_name").toString());
    QVersionNumber currVersion  = QVersionNumber::fromString(qApp->applicationVersion());

    qDebug()<<"last version " << lastVersion;
    qDebug()<<"current version " << currVersion;

    if (lastVersion > currVersion){
        mLabel->setText(tr("A new version %1 is avaible").arg(lastVersion.toString()));
        mDLUrl = QUrl(doc.object().value("html_url").toString());
        mDLButton->setVisible(true);
    }

    else
    {
        mLabel->setText(tr("You already have the latest update"));
        mDLButton->setVisible(false);
    }

    reply->deleteLater();

}

void UpdateDialog::openUrl()
{
    QDesktopServices::openUrl(mDLUrl);
}
