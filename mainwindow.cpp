#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ssh = new SSH(this);
    connect(ui->actionNew,&QAction::triggered,[this]{
        ssh->init();
    });

    connect(ui->actionExit,&QAction::triggered,[this]{
        if(ssh->isWorking())
            ssh->myExit();
    });
    connect(ssh,&SSH::Exit,this,&QMainWindow::close);

    connect(ui->actionRefresh,&QAction::triggered,[this]{
        if(ssh->isWorking()){
            ssh->refresh();
        }
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
        connect(actionDownload,&QAction::triggered,[this]{
            QString name = ui->listView->currentIndex().data().toString();
            ssh->download(name);
        });
        menu->exec(QCursor::pos());
        ui->listView->selectionModel()->clear();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ssh;
}

