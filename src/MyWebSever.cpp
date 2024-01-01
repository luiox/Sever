#include "hv/HttpService.h"
#include <MyWebSever.h>
#include <spdlog/spdlog.h>

MyWebServer::MyWebServer(int port) { 
    m_sever = new http_server_t;
    m_router= new hv::HttpService;
    m_thread_pool = new HThreadPool(1,3);
    // m_thread_pool->commit(Fn &&fn, Args &&args...)
}

MyWebServer::~MyWebServer()
{
    delete m_sever;
    delete m_router;
    delete m_thread_pool;
}

void MyWebServer::start()
{

}
