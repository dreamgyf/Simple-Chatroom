#include "thread.h"

Thread::Thread(SOCKET &sock, QObject *parent)
{
    this->sock = sock;
}

void Thread::run()
{
    char msg[65535];
    while(1)
    {
        memset(msg,0,sizeof(msg));
        if(recv(sock,msg,sizeof(msg),0) > 0)
        {
            text += QString(msg);
            emit go(text);
        }
    }
}
