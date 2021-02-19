#ifndef SSH_H
#define SSH_H

#include <QObject>
#include <QFile>
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
    void init();
    void write(const QString&);
    void updateName(QString&);
    void update();
    void myExit();

    bool isWorking()
    {return activing;}

    void refresh();
public slots:
    void download(QString&);

private:
    QProcess* p;
    QString path,name;
    Download* d;

    bool activing = false;

signals:
    void updatePath(QString&);
    void sendFormat(const QList<FileFormat>&);
    void Exit();
};

#endif // SSH_H
