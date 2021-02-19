#ifndef NEWUSER_H
#define NEWUSER_H

#include <QDialog>

namespace Ui {
class NewUser;
}

class NewUser : public QDialog
{
    Q_OBJECT

public:
    explicit NewUser(QWidget *parent = nullptr);
    ~NewUser();
signals:
    void send(const QString&);
private:
    Ui::NewUser *ui;
};

#endif // NEWUSER_H
