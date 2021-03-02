#include "HTTP.h"

HTTP::HTTP(QObject *parent) : QObject(parent)
{
    dir.setCurrent(saveDir);
    d = new HttpDownload(dir);
}

void HTTP::setHost(const User &h)
{
    host="http://"+h.addr;
    dirmask = "/home/"+h.user+"/http";
}

void HTTP::setSavePath(const QString &s)
{
    saveDir=s;
    d->setDir(saveDir);
}

void HTTP::setCurrDir(const QString &d)
{
    QString o = d;
    o=o.remove("\n");
    currdir = o.mid(dirmask.size());
}

void HTTP::download(const FileFormat&n)
{
    QString name = n.getName();
    QString target = host+currdir+"/"+name;

    if(n.getType() == FileFormat::FILE){
//        qDebug()<<target;
        d->downloadFile(name,target);
    }
    if(n.getType() == FileFormat::DIR){
//        qDebug()<<target+"/";
        d->download(name,target+"/");
    }
}
