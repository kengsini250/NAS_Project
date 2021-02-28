#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QMimeData>
#include <QDragEnterEvent>

#include <QDebug>

#include "SSH.h"
#include "HTTP.h"
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
    HTTP* http;
    Setting* setting;
    NewUser* newuser;

    //?
    QList<FileFormat> currList;
private:
    Ui::MainWindow *ui;

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
};
#endif // MAINWINDOW_H
