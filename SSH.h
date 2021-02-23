#ifndef SSH_H
#define SSH_H

#include <QObject>
#include <QFile>
#include <QStandardPaths>
#include <QProcess>
#include "shell.h"
#include "download.h"
#include "FileFormat.h"

class SSH : public QObject
{
    Q_OBJECT
public:
    ~SSH();
    SSH(QObject *ptr = nullptr);
    void write(const QString&);
    void updateName(QString&);
    void update();

    bool isWorking()
    {return activing;}

public slots:
    void download(QString&);
    void setHost(const QString&);
    void setSavePath(const QString&);
    void upload(const QString&);
    void remove(const QString&);
    void refresh();
    void myExit();

private:
    QProcess* p;
    QString path,name;
    Download* d;
    QString savePath = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).at(0);
    QString host;

    bool activing = false;
    void init();
signals:
    void uploading(const QString&);
    void uploadFinished(const QString&);
    void downloading(const QString&);


    void updatePath(QString&);
    void sendFormat(const QList<FileFormat>&);
    void Exit();
};

#endif // SSH_H
