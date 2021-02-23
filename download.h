#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QFile>
#include <QProcess>
#include <QString>
#include <QStringList>

#include <QDebug>

class Download : public QObject
{
    Q_OBJECT
public:
    ~Download();
    Download() = delete;
    explicit Download(QObject *parent = nullptr);
    void setSource(QString p,QString n);
    void setTarget(QString t);
    void setHost(QString h);

    void download();
    void upload(const QString&);
private:
    QString path,name,target,host;
    QString dirflag = "";
    QProcess* d;
signals:
    void downloading(const QString&);
    void downloadFinished(const QString&);
    void uploading(const QString&);
    void uploadFinished(const QString&);
};

#endif // DOWNLOAD_H
