#include "HTTP.h"

HTTP::HTTP(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
    dir.setCurrent(saveDir);
}

void HTTP::init()
{
    connect(manager,&QNetworkAccessManager::finished,[this](QNetworkReply *reply){
        if(reply->error() == QNetworkReply::NoError){
            QByteArray bytes = reply->readAll();

            QFile file(fileTemp);
            if (file.open(QIODevice::Append)){
                file.write(bytes);
            }
            file.close();
        }
    });
}

void HTTP::setHost(const User &h)
{
    host="http://"+h.addr;
    rootDirMask = "/home/"+h.user+"/http";
    init();
}

void HTTP::setSavePath(const QString &s)
{
    saveDir=s;
}

void HTTP::setCurrDir(const QString &s)
{
    QString o = s;
    currDir = o.replace(rootDirMask,"").remove("\n");
}

void HTTP::download(const FileFormat&n)
{
    currFile = n.getName();
    auto currType = n.getType();
    QString currpath=host+currDir+"/"+currFile;	//qDebug()<<currpath;

    if(currType == FileFormat::FILE){
        fileTemp=currFile;
        Download(currpath);
    }

    if(currType == FileFormat::DIR){
        dir.mkdir(currFile);
        dir.setCurrent(currFile);
        getAll(currpath);
        connect(this,&HTTP::httpGetFinished,[this,currpath](const QStringList &d){
            for(auto p : d){
                if(p.right(0) == "/"){
                    download(FileFormat{FileFormat::DIR,p});
                }else{
                    fileTemp=p;
                    Download(currpath+"/"+p);
                }
            }
        });
    }

}

void HTTP::getAll(const QString &p)
{
    qDebug()<<p;
    QNetworkAccessManager *_manager = new QNetworkAccessManager(this);
    QNetworkRequest _request;
    _request.setUrl(p+"/");
    connect(_manager,&QNetworkAccessManager::finished,[this](QNetworkReply *reply){
        if(reply->error() == QNetworkReply::NoError){
            QByteArray bytes = reply->readAll();
            QStringList curr=Reg(bytes);
            emit httpGetFinished(curr);
        }
        else
            qDebug()<<"wrong"<<reply->error();
    });
    _manager->get(request);
}

void HTTP::Download(const QString &p)
{
    request.setUrl(p);
    manager->get(request);
}
