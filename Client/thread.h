#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <QThread>
#include <QString>
#include <winsock2.h>

class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(SOCKET &sock,QObject *parent = nullptr);

private:
    SOCKET sock;
    QString text;
protected:
    void run();

signals:
    void go(QString);
};

#endif // THREAD_H
