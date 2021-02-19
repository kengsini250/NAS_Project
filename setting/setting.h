#ifndef SETTING_H
#define SETTING_H

#include <QDialog>
#include <QString>

namespace Ui {
class Setting;
}

class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();
signals:
    void send(const QString&);
private:
    Ui::Setting *ui;
};

#endif // SETTING_H
