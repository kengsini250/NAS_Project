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
        emit Exit();
    });

    p->start(shell::ssh,QStringList()<<host);
    p->waitForStarted();
    write(shell::ls_al);

    connect(d,&Download::uploadFinished,[this]{refresh();});
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
    p->waitForFinished();
    p->close();
    activing = false;
}

void SSH::refresh()
{
    write(shell::ls_al);
}

void SSH::download(QString &name)
{
    d->setHost(host);
    d->setSource(path,name);
    d->setTarget(savePath);
    d->download();
}

void SSH::setHost(const QString &h)
{
    host = h;
    init();
}

void SSH::setSavePath(const QString &p)
{
    savePath = p;
}

void SSH::upload(const QString &p)
{
    d->setHost(host);
    d->setSource(path,"");
    d->upload(p);
}

void SSH::remove(const QString &f)
{
    write(shell::remove(f));
    refresh();
}
