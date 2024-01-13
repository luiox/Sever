#include <MyWebSever.h>
#include <hv/EventLoop.h>
#include <hv/HttpService.h>
#include <spdlog/spdlog.h>
#include <thread>

MyWebServer::MyWebServer(int port)
{
    m_sever = new http_server_t;
    m_router = new hv::HttpService;
    m_thread_pool = new HThreadPool(1, 3);
    // m_thread_pool->commit(Fn &&fn, Args &&args...)
}

MyWebServer::~MyWebServer()
{
    delete m_sever;
    delete m_router;
    delete m_thread_pool;
}

// 自己负责自己的线程启动工作
// 把自己的线程启动工作交给外部
void
MyWebServer::startWebSever(int port)
{
    spdlog::info("Web Server thread is starting...");
    MyWebServer web_server(port);
    std::thread web_thread([&web_server]() { web_server.run(); });
}

void
MyWebServer::run()
{
    hv::EventLoopPtr loop(new hv::EventLoop);

    loop->run();
}
