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
    emit downloading(name);
    d->start("scp",QStringList()<<"-r"<<host+path<<target);
    d->waitForStarted();
    emit downloadFinished(name);
/*
    connect(d,&QProcess::readyReadStandardOutput,[this]{
        QByteArray data = d->readAllStandardOutput();
        QFile file(name);
        if (file.open(QIODevice::Append))
            file.write(data);
        file.close();
        d->close();
    });
*/
}

void Download::upload(const QString &p)
{
    emit uploading(p);
    d->start("scp",QStringList()<<"-r"<<p<<host+path);
    d->waitForStarted();
    emit uploadFinished(p);
}
