#ifndef HTTP_H
#define HTTP_H

#include <QObject>
#include <QString>
#include <QStandardPaths>

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QDir>

#include "FileFormat.h"
#include "httpdownload.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QRegularExpressionMatchIterator>

class HTTP : public QObject
{
    Q_OBJECT
public:
    explicit HTTP(QObject *parent = nullptr);
    void setHost(const User&);
public slots:
    void setSavePath(const QString&);
    void setCurrDir(const QString&);
    void download(const FileFormat&);
    void upload(const QString&){}
private:
    QString host,currdir,dirmask;
//    QString saveDir = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).at(0);
    QString saveDir = "C:\\Users\\kengs\\Desktop\\";
    int port=-1;
    bool activing=false;
    QDir dir;
    HttpDownload *d;

signals:
    void httpGetFinished(const QStringList&);
    void uploading(const QString&);
    void uploadFinished(const QString&);
    void downloading(const QString&);
};

#endif // HTTP_H