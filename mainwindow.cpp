#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::bind(Presenter *p)
{
    this->p = p;
    mvpInit();
}

void MainWindow::mvpInit()
{
    connect(ui->actionNew,&QAction::triggered,this,[this]{
        p->newuser_show();
    });
    connect(ui->actionproperty,&QAction::triggered,this,[this]{
        p->setting_show();
    });
    connect(ui->actionExit,&QAction::triggered,this,[this]{
        p->sshExit();
    });

    ui->listView->setViewMode(QListView::IconMode);
    connect(p,&Presenter::presenter2mainwindow_sendFormat,this,[this](const QList<FileFormat> &data){
        currList = data;
        QStandardItemModel* fileItem = new QStandardItemModel(this);
        auto p = data.begin();
        while (p != data.end())
        {
            QStandardItem* file = new QStandardItem((*p).getName());
            if((*p).getType() == FileFormat::DIR){file->setIcon(QIcon(":/pic/dir.png"));}
            if((*p).getType() == FileFormat::FILE){file->setIcon(QIcon(":/pic/file.png"));}
            fileItem->appendRow(file);
            p++;
        }
        ui->listView->setModel(fileItem);
    });

     ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
     connect(ui->listView,&QListView::doubleClicked,this,[&](QModelIndex index){
             QString name = index.data().toString();
             emit mainwindow2presenter_openFile(name);
             emit mainwindow2presenter_pwd();
     });

     ui->textEdit->setReadOnly(1);
     connect(p,&Presenter::presenter2mainwindow_pwd,this,[this](const QString& p){
         ui->textEdit->clear();
         ui->textEdit->append(p.split("\n").at(0));
     });

     ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);
     connect(ui->listView,&QWidget::customContextMenuRequested,this,[this]{
         QMenu* menu = new QMenu(ui->listView);
         QAction *actionDownload = menu->addAction("download");
         QAction *actionDelete = menu->addAction("delete");
         connect(actionDownload,&QAction::triggered,this,[this]{
             QString name = ui->listView->currentIndex().data().toString();
             for(auto &p : currList){
                 if(p.getName() == name && p.getName() != ".."&& p.getName() != "."){
                     emit mainwindow2presenter_setCurrDir(ui->textEdit->toPlainText());
                     emit mainwindow2presenter_download(p);
                 }
             }
         });
         connect(actionDelete,&QAction::triggered,this,[this]{
             QString name = ui->listView->currentIndex().data().toString();
             emit mainwindow2presenter_remove(name);
         });
         menu->exec(QCursor::pos());
         ui->listView->selectionModel()->clear();
     });
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
        /*
        auto allFile = mimeData->urls();
        for(auto &p : allFile){
            http->upload(p.toLocalFile());
        }
        */
    }
}

