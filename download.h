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
    void downloadFinished();
    void uploadFinished();
};

#endif // DOWNLOAD_H
