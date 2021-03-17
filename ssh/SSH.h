#ifndef SSH_H
#define SSH_H

#include <QObject>
#include <QFile>
#include <QStandardPaths>
#include <QProcess>
#include <QDebug>

#include "../presenter.h"
#include "shell.h"
#include "FileFormat.h"

class SSH : public QObject
{
    Q_OBJECT
public:
    ~SSH();
    SSH(QObject *ptr = nullptr);
    void bind(Presenter* p);
    void write(const QString&);

    bool isWorking()
    {return activing;}

public slots:
    void cd(const QString&);
    void pwd();
    void setHost(const User&);
    void remove(const QString&);
    void refresh();
    bool myExit();

private:
    Presenter* p;
    QProcess* proc;
    QString path,name;
    QString savePath = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).at(0);
    QString host;

    bool activing = false;
    void init();
signals:
    void ssh2presenter_pwd(const QString&);
    void ssh2presenter_sendFormat(const QList<FileFormat>&);
};

#endif // SSH_H
