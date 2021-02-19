#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>
#include <QStringList>
#include <QByteArray>

#include <QDebug>

#include "SSH.h"
#include "setting/setting.h"
#include "newuser/newuser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    SSH* ssh;
    Setting* setting;
    NewUser* newuser;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
