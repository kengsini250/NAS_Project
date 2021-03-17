#ifndef DOWNLOADQUEUE_H
#define DOWNLOADQUEUE_H

#include <QWidget>
//test
#include <QPainter>
#include <QPaintEvent>
//

namespace Ui {
class DownloadQueue;
}

class DownloadQueue : public QWidget
{
    Q_OBJECT

public:
    explicit DownloadQueue(QWidget *parent = nullptr);
    void setSize(int w,int h);
    int getWidth();
    int getHeight();
    ~DownloadQueue();
protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::DownloadQueue *ui;
};

#endif // DOWNLOADQUEUE_H
