#include "downloadqueue.h"
#include "ui_downloadqueue.h"

DownloadQueue::DownloadQueue(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownloadQueue)
{
    ui->setupUi(this);
}

void DownloadQueue::setSize(int w, int h)
{
    resize(w,h);
}

int DownloadQueue::getWidth()
{
    return width();
}

int DownloadQueue::getHeight()
{
    return height();
}

DownloadQueue::~DownloadQueue()
{
    delete ui;
}

void DownloadQueue::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter p(this);
    p.setBrush(Qt::blue);
    p.drawRect(QRect(0,0,width(),height()));
}
