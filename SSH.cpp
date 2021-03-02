#include "SSH.h"

SSH::~SSH()
{
    if(!activing){
        delete p;
    }
}

SSH::SSH(QObject *parent) : QObject(parent)
{
    p = new QProcess(this);
    activing = true;
}

void SSH::init()
{
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
    write(shell::NextUpdate("http"));//same as http
    p->waitForReadyRead();
    refresh();
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
    if(isWorking()){
        p->write("exit\n");
        p->waitForFinished();
        p->close();
    }
    activing = false;
}

void SSH::refresh()
{
    if(isWorking()){
        write(shell::ls_al);
        write("pwd");
    }
}

void SSH::setHost(const User &h)
{
    host = h.user+"@"+h.addr;
    init();
}

void SSH::remove(const QString &f)
{
    write(shell::remove(f));
    refresh();
}
