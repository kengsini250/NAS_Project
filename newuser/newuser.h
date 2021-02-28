#ifndef NEWUSER_H
#define NEWUSER_H

#include <QDialog>
#include "../FileFormat.h"

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
    void send(const User&);
private:
    Ui::NewUser *ui;
};

#endif // NEWUSER_H
