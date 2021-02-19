#include "download.h"

Download::~Download()
{
    delete d;
}

Download::Download(QObject *parent) : QObject(parent)
{
    d = new QProcess(this);
}

void Download::setSource(QString p, QString n)
{
    name = n;
    path = p.remove('\n')+"/"+n;
}

void Download::setTarget(QString t)
{
    target = t;
}

void Download::setHost(QString h)
{
    host = h+":";
}

void Download::download()
{
    d->start("scp",QStringList()<<"-r"<<host+path<<target);

    connect(d,&QProcess::readyReadStandardOutput,[this]{
        QByteArray data = d->readAllStandardOutput();
        QFile file(name);
        if (file.open(QIODevice::Append))
            file.write(data);
        file.close();
        d->close();
    });
    emit downloadFinished();
}

void Download::upload(const QString &p)
{
    qDebug()<<"scp -r"<<p<<host+path;
    d->start("scp",QStringList()<<"-r"<<p<<host+path);
    emit uploadFinished();
}
