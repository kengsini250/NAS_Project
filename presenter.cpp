#include "presenter.h"
#include "mainwindow.h"
#include "newuser/newuser.h"
#include "setting/setting.h"
#include "http/HTTP.h"
#include "ssh/SSH.h"

Presenter::Presenter(QObject *parent) : QObject(parent)
{
    newUser = new NewUser;
    newUser->bind(this);
    setting = new Setting;
    setting->bind(this);
    mainWindow = new MainWindow;
    mainWindow->bind(this);
    ssh = new SSH;
    ssh->bind(this);
    http = new HTTP;
    http->bind(this);

    //login
    connect(newUser,&NewUser::send,ssh,&SSH::setHost);
    connect(newUser,&NewUser::send,http,&HTTP::setHost);
    //mainwindow
    connect(mainWindow,&MainWindow::mainwindow2presenter_pwd,ssh,&SSH::pwd);
    connect(mainWindow,&MainWindow::mainwindow2presenter_download,http,&HTTP::download);
    connect(mainWindow,&MainWindow::mainwindow2presenter_remove,ssh,&SSH::remove);
    connect(mainWindow,&MainWindow::mainwindow2presenter_setCurrDir,http,&HTTP::setCurrDir);
    connect(mainWindow,&MainWindow::mainwindow2presenter_openFile,ssh,&SSH::cd);
    //ssh
    connect(ssh,&SSH::ssh2presenter_sendFormat,this,[this](const QList<FileFormat> &f){
        emit presenter2mainwindow_sendFormat(f);
    });
    connect(ssh,&SSH::ssh2presenter_pwd,this,[this](const QString& p){
        emit presenter2mainwindow_pwd(p);
    });
    //setting
    connect(setting,&Setting::send,http,&HTTP::setSavePath);
}

Presenter::~Presenter()
{
    delete newUser;
    delete setting;
    delete ssh;
    delete http;
    delete mainWindow;
}

void Presenter::show()
{
    mainWindow->show();
}

void Presenter::newuser_show()
{
    newUser->show();
}

void Presenter::setting_show()
{
    setting->show();
}

bool Presenter::sshExit()
{
    return ssh->myExit();
}
