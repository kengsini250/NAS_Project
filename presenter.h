#ifndef PRESENTER_H
#define PRESENTER_H

#include <QObject>
#include "FileFormat.h"

class MainWindow;
class NewUser;
class SSH;
class HTTP;
class Setting;

class Presenter : public QObject
{
    Q_OBJECT
public:
    Presenter(QObject *parent = nullptr);
    ~Presenter();
    void show();
    void newuser_show();
    void setting_show();
    bool sshExit();
signals:
    //2mainwindow
    void presenter2mainwindow_sendFormat(const QList<FileFormat>&);
    void presenter2mainwindow_pwd(const QString&);
private:
    NewUser* newUser;
    Setting* setting;
    MainWindow* mainWindow;
    SSH* ssh;
    HTTP* http;
};

#endif // PRESENTER_H
