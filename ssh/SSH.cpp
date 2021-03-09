#include "SSH.h"

SSH::~SSH()
{
    if(!activing){
        delete p;
    }
}

SSH::SSH(QObject *parent) : QObject(parent)
{
    proc = new QProcess(this);
    activing = true;
}

void SSH::bind(Presenter *p)
{
    this->p=p;
}

void SSH::init()
{
    connect(proc,&QProcess::readyReadStandardError,this,[this]{
        QByteArray data = proc->readAllStandardError();
        qDebug()<<data;
    });

    connect(proc,&QProcess::readyReadStandardOutput,this,[this]{
        QByteArray data = proc->readAllStandardOutput();
        QString t = data;
        if(t[0] == "/"){
            path = t;
            emit ssh2presenter_pwd(path);
        }else if(t[0] == "t"){
            emit ssh2presenter_sendFormat(FileFormat::makeFileFormat(t));
        }
    });

    connect(proc,QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),[=](int exitCode, QProcess::ExitStatus exitStatus){
        Q_UNUSED(exitCode);
        Q_UNUSED(exitStatus);
        emit Exit();
    });

    proc->start(shell::ssh,QStringList()<<host);
    proc->waitForStarted();
    write(shell::NextUpdate("http"));//same as http
    proc->waitForReadyRead();
    refresh();
}

void SSH::write(const QString &msg)
{
    proc->write(msg.toUtf8()+'\n');
}

void SSH::cd(const QString &name)
{
    write(shell::NextUpdate(name));
    write("pwd");
    this->name = name;
}

void SSH::pwd()
{
        write("pwd");
}

void SSH::myExit()
{
    if(isWorking()){
        proc->write("exit\n");
        proc->waitForFinished();
        proc->close();
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
    qDebug()<<host;
    init();
}

void SSH::remove(const QString &f)
{
    write(shell::remove(f));
    refresh();
}
