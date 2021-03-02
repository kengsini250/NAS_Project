#include "HTTP.h"

HTTP::HTTP(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    dir.setCurrent(saveDir);
    d = new HttpDownload(dir);
}

void HTTP::setHost(const User &h)
{
    host="http://"+h.addr;
}

void HTTP::setSavePath(const QString &s)
{
    saveDir=s;
    d->setDir(saveDir);
}

void HTTP::download(const FileFormat&n)
{
    if(n.getType() == FileFormat::FILE){
        d->downloadFile(n.getName(),host+"/"+n.getName()+"/");
    }
    if(n.getType() == FileFormat::DIR){
        d->download(n.getName(),host+"/"+n.getName()+"/");
    }
}
