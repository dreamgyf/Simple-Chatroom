#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QMessageBox>
#include "client.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void onlinkbutton();
    ~Widget();

private:
    Ui::Widget *ui;
    QLineEdit *name = new QLineEdit(this);
    QLineEdit *ip = new QLineEdit(this);
    QPushButton *ok = new QPushButton(u8"连接",this);
    QPushButton *exit = new QPushButton(u8"退出",this);
    QLabel *l_name = new QLabel(u8"昵称:",this);
    QLabel *l_ip = new QLabel(u8"IP:",this);

    QString s_ip = "118.31.67.250";
    QString s_name;

    Client *client;

public slots:
    void show_main();
    void quit();
};

#endif // WIDGET_H
