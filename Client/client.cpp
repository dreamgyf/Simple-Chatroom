#include "client.h"
#include <qdebug.h>

Client::Client(QString name, QString ip, int port,QObject *parent) : QObject(nullptr)
{
    this->name = name;
    this->ip = ip;
    this->port = port;
    if(WSAStartup(MAKEWORD(2,2),&wsadata) != 0)
        error = true;
    if((sock = socket(PF_INET,SOCK_STREAM,0)) == INVALID_SOCKET)
        error = true;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.S_un.S_addr = inet_addr(ip.toStdString().c_str());
    addr.sin_port = htons(port);
    if(::connect(sock,(SOCKADDR *)&addr,sizeof(addr)) == SOCKET_ERROR)
        error = true;
}

Client::~Client()
{
    if(com != nullptr)
        delete com;
}

bool Client::have_error() const
{
    return error ? true : false;
}

void Client::communication()
{
    com = new Communication(name);
    connect(com,&Communication::send,this,&Client::send_message);
    connect(com,&Communication::return_widget,this,&Client::return_widget);
    connect(com,&Communication::quit,this,&Client::quit);
    emit widgethide();
    com->show();

    Thread *thread = new Thread(sock);
    connect(thread,SIGNAL(go(QString)),this,SLOT(updateui(QString)));
    thread->start();
}

void Client::closeclient()
{
    closesocket(sock);
    WSACleanup();
}

void Client::send_message()
{
    if(com->gettext().isEmpty())
        return;

    QByteArray temp = (name + QString(":") + com->gettext() + QString("\n")).toUtf8();
    string s_temp = string(temp);
    char *msg = new char[(int)s_temp.length() + 1];
    strcpy(msg,s_temp.c_str());
    ::send(sock,msg,strlen(msg),0);
    delete msg;
    msg = nullptr;
    com->clean();
}

void Client::updateui(QString text)
{
    com->settext(text);
}

void Client::return_widget()
{
    closeclient();
    delete com;
    com = nullptr;
    emit widgetshow();
}

void Client::quit()
{
    closeclient();
    delete com;
    com = nullptr;
    emit s_quit();
}
