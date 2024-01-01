#ifndef MY_WEB_SERVER_H
#define MY_WEB_SERVER_H

#include <hv/HttpServer.h>
#include <hv/hthreadpool.h>
#include <memory>

class MyWebServer {
public:
    MyWebServer(int port = 7777);
    ~MyWebServer();

    void start();

private:
    http_server_t* m_sever;
    HttpService* m_router;
    HThreadPool* m_thread_pool;
};

#endif // MY_WEB_SERVER_H
