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
    void myExit();

    bool isWorking()
    {return activing;}

    void refresh();
public slots:
    void download(QString&);
    void setHost(const QString&);
    void setSavePath(const QString&);
    void upload(const QString&);
    void remove(const QString&);

private:
    QProcess* p;
    QString path,name;
    Download* d;
    QString savePath = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).at(0);
    QString host;

    bool activing = false;
    void init();
signals:
    void updatePath(QString&);
    void sendFormat(const QList<FileFormat>&);
    void Exit();
};

#endif // SSH_H
