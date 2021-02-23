#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);

    ssh = new SSH(this);
    //new user
    newuser = new NewUser(this);
    connect(newuser,&NewUser::send,ssh,&SSH::setHost);
    connect(ui->actionNew,&QAction::triggered,[this]{
        newuser->show();
    });

    connect(ui->actionExit,&QAction::triggered,ssh,&SSH::myExit);
    connect(ssh,&SSH::Exit,this,&QMainWindow::close);
    connect(ui->actionRefresh,&QAction::triggered,ssh,&SSH::refresh);

    connect(ssh,&SSH::downloading,[this](const QString&n){
        ui->statusbar->showMessage("downloading... "+n);
    });
    connect(ssh,&SSH::uploading,[this](const QString&n){
        ui->statusbar->showMessage("uploading... "+n);
    });
    connect(ssh,&SSH::uploadFinished,[this](const QString&n){
        ui->statusbar->showMessage(n+" finished");
    });

    ui->listView->setViewMode(QListView::IconMode);
    connect(ssh,&SSH::sendFormat,[this](const QList<FileFormat> &data){
        QStandardItemModel* fileItem = new QStandardItemModel(this);
        auto p = data.begin();
        while (p != data.end())
        {
            QStandardItem* file = new QStandardItem((*p).getName());
            if((*p).getType().at(0) == "d"){file->setIcon(QIcon(":/pic/dir.png"));}
            if((*p).getType().at(0) == "-"){file->setIcon(QIcon(":/pic/file.png"));}
            fileItem->appendRow(file);
            p++;
        }
        ui->listView->setModel(fileItem);
    });

    ui->textEdit->setReadOnly(1);
    connect(ssh,&SSH::updatePath,[this](QString& data){
        ui->textEdit->clear();
        ui->textEdit->append(data);
    });

    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->listView,&QListView::doubleClicked,[&](QModelIndex index){
        QString name = index.data().toString();
        ssh->write(shell::NextUpdate(name));
        ssh->update();
        ssh->updateName(name);
    });

    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listView,&QWidget::customContextMenuRequested,[this]{
        QMenu* menu = new QMenu(ui->listView);
        QAction *actionDownload = menu->addAction("download");
        QAction *actionDelete = menu->addAction("delete");
        connect(actionDownload,&QAction::triggered,[this]{
            QString name = ui->listView->currentIndex().data().toString();
            ssh->download(name);
        });
        connect(actionDelete,&QAction::triggered,[this]{
            QString name = ui->listView->currentIndex().data().toString();
            ssh->remove(name);
        });
        menu->exec(QCursor::pos());
        ui->listView->selectionModel()->clear();
    });

    //setting
    setting = new Setting(this);
    connect(setting,&Setting::send,ssh,&SSH::setSavePath);
    connect(ui->actionproperty,&QAction::triggered,[this]{
        setting->show();
    });
}

MainWindow::~MainWindow()
{
    if(ssh->isWorking())
        ssh->myExit();
    delete ui;
    delete ssh;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasUrls())
        event->acceptProposedAction();
    else
        event->ignore();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if(mimeData->hasUrls()){
        auto allFile = mimeData->urls();
        for(auto p : allFile){
            ssh->upload(p.toLocalFile());
        }
    }
}

