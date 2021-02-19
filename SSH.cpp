#include "SSH.h"


SSH::~SSH()
{
    delete p;
    delete d;
}

SSH::SSH(QObject *parent) : QObject(parent)
{
    p = new QProcess(this);
    activing = true;
}

void SSH::init()
{
    d = new Download(this);

    connect(p,&QProcess::readyReadStandardError,[this]{
        QByteArray data = p->readAllStandardError();
        qDebug()<<data;
    });

    connect(p,&QProcess::readyReadStandardOutput,[this]{
        QByteArray data = p->readAllStandardOutput();
        QString t = data;
        if(t[0] == "/"){
            path = t;
            emit updatePath(path);
        }else if(t[0] == "t"){
            emit sendFormat(FileFormat::makeFileFormat(t));
        }
    });

    connect(p,QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),[=](int exitCode, QProcess::ExitStatus exitStatus){
        Q_UNUSED(exitCode);
        Q_UNUSED(exitStatus);
        p->write("exit\n");
        p->waitForFinished();
        p->close();
        emit Exit();
    });

    p->start(shell::ssh,QStringList()<<"oppai@192.168.2.46");
    p->waitForStarted();
    write(shell::ls_al);
}

void SSH::write(const QString &msg)
{
    p->write(msg.toUtf8()+'\n');
}

void SSH::updateName(QString &n)
{
    name = n;
}

void SSH::update()
{
    write("pwd");
}

void SSH::myExit()
{
    p->write("exit\n");
    activing = false;
}

void SSH::refresh()
{
    write(shell::ls_al);
}

void SSH::download(QString &name)
{
    d->setHost("oppai@192.168.2.46");
    d->setSource(path,name);
    d->setTarget("C:\\Users\\kengs\\Desktop\\");
    d->download();
}