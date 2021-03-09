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

#include "FileFormat.h"
#include "presenter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void bind(Presenter* p);

signals:
    void mainwindow2presenter_pwd();
    void mainwindow2presenter_openFile(const QString&);

    void mainwindow2presenter_setCurrDir(const QString&);
    void mainwindow2presenter_download(const FileFormat&);
    void mainwindow2presenter_remove(const QString&);
private:
    Ui::MainWindow *ui;
    QList<FileFormat> currList;
    Presenter* p;

    void mvpInit();
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
};
#endif // MAINWINDOW_H
