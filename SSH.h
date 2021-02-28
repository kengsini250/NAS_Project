#ifndef SSH_H
#define SSH_H

#include <QObject>
#include <QFile>
#include <QStandardPaths>
#include <QProcess>
#include <QDebug>

#include "shell.h"
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
    void setHost(const User&);
    void remove(const QString&);
    void refresh();
    void myExit();

private:
    QProcess* p;
    QString path,name;
    QString savePath = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).at(0);
    QString host;

    bool activing = false;
    void init();
signals:
    void updatePath(const QString&);
    void sendFormat(const QList<FileFormat>&);
    void Exit();
};

#endif // SSH_H
