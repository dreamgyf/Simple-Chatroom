#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QLatin1String>
#include <string>
#include <cstring>
#include <winsock2.h>
#include <pthread.h>
#include <QMutex>
#include <QByteArray>
#include "communication.h"
#include "thread.h"

using namespace std;



class Client : public QObject
{
    Q_OBJECT
public:
    Client(QString name,QString ip,int port,QObject *parent = 0);
    ~Client();
    bool have_error() const;
    void communication();
    void closeclient();
    void send_message();

private:
    WSADATA wsadata;
    SOCKET sock;
    SOCKADDR_IN addr;
    QString name;
    QString ip;
    int port;
    bool error = false;

    Communication *com;
signals:
    void widgethide();
    void widgetshow();
    void s_quit();
public slots:
    void return_widget();
    void quit();
    void updateui(QString);
};

#endif // CLIENT_H
