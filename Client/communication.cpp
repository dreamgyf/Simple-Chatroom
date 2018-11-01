#include "communication.h"

Communication::Communication(QString name, QWidget *parent) : QWidget(parent)
{
    setWindowTitle(u8"聊天室demo");
    setMinimumSize(300,600);
    setMaximumSize(300,600);
    l_name = new QLabel(u8"昵称:"+name,this);
    l_name->setGeometry(30,10,200,30);
    t_recv = new QTextEdit(this);
    t_recv->setReadOnly(true);
    t_recv->setGeometry(30,40,240,400);
    t_send = new QTextEdit(this);
    t_send->setGeometry(30,470,190,100);
    b_send = new QPushButton(u8"发送",this);
    b_send->setGeometry(230,470,50,25);
    b_return = new QPushButton(u8"返回",this);
    b_return->setGeometry(230,505,50,25);
    b_exit = new QPushButton(u8"退出",this);
    b_exit->setGeometry(230,540,50,25);
    connect(b_send,SIGNAL(clicked(bool)),this,SIGNAL(send()));
    connect(b_return,SIGNAL(clicked(bool)),this,SIGNAL(return_widget()));
    connect(b_exit,SIGNAL(clicked(bool)),this,SIGNAL(quit()));
}

Communication::~Communication()
{
    delete l_name;
    delete t_recv;
    delete t_send;
    delete b_send;
    delete b_return;
    delete b_exit;
}

QString Communication::gettext()
{
    return t_send->toPlainText();
}

void Communication::settext(QString text)
{
    t_recv->setText(text);
}

void Communication::clean()
{
    t_send->setText(QString());
}
