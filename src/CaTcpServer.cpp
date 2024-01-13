#include <CaTcpServer.h>
#include <thread>

CaTcpServer::CaTcpServer()
    :m_loop(hloop_new(0))) {

}
CaTcpServer::~CaTcpServer() {}
void
CaTcpServer::startTcpServer(int port)
{
    CaTcpServer tcp_server;
    std::thread tcp_thread([&tcp_server]() { tcp_server.run(); });
    tcp_thread.join();
}
void
CaTcpServer::run()
{
    HT

}