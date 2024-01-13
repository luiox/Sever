#ifndef CA_TCP_SERVER_H
#define CA_TCP_SERVER_H

#include <hv/hloop.h>

class CaTcpServer
{
public:
    CaTcpServer();
    ~CaTcpServer();
    static void startTcpServer(int port = 7777);
    void run();

private:
    hloop_t * m_loop;
};

#endif // !CA_TCP_SERVER_H