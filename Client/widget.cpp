#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle(u8"聊天室demo");
    name->setGeometry(95,100,150,20);
    ip->setGeometry(95,150,150,20);
    ip->setText(s_ip);
    l_name->setGeometry(60,100,30,20);
    l_ip->setGeometry(60,150,30,20);
    ok->setGeometry(100,300,100,30);
    exit->setGeometry(100,350,100,30);
    connect(ok,&QPushButton::clicked,this,&Widget::onlinkbutton);
    connect(exit,&QPushButton::clicked,this,&Widget::close);
}

Widget::~Widget()
{
    delete ui;
    delete name;
    delete ip;
    delete ok;
    delete exit;
    delete l_name;
    delete l_ip;
    if(client != nullptr)
    {
        delete client;
        client = nullptr;
    }
}

void Widget::onlinkbutton()
{
    if(name->text().isEmpty())
        s_name = "no name";
    else
        s_name = name->text();
    s_ip = ip->text();
    client = new Client(s_name,s_ip,6666);
    connect(client,&Client::widgethide,this,&Widget::hide);
    connect(client,&Client::widgetshow,this,&Widget::show_main);
    connect(client,&Client::s_quit,this,&Widget::quit);
    if(client->have_error())
    {
        client->closeclient();
        delete client;
        client = nullptr;
        QMessageBox fail(this);
        fail.warning(this,u8"连接失败",u8"连接失败!");
    }
    else
    {
        client->communication();
    }
}

void Widget::show_main()
{
    client->closeclient();
    delete client;
    client = nullptr;
    show();
}

void Widget::quit()
{
    client->closeclient();
    delete client;
    client = nullptr;
    close();
}
