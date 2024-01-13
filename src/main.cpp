#include <MyWebSever.h>
#include <hv/EventLoop.h>
#include <hv/HttpServer.h>
#include <hv/hloop.h>
#include <hv/hversion.h>
#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>
using namespace std;
const char * SeverVersion = "0.1.0";

int
main()
{
    // // 初始化spdlog，同时输出到shell和文件
    // auto console_sink = std::make_shared<spdlog::sinks::stdout_sink_mt>();
    // auto file_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(
    //   "log/sever",
    //   23,
    //   59); // 在log目录下生成按日期命名的日志文件
    // auto logger = std::make_shared<spdlog::logger>(
    //   "logger",
    //   spdlog::sinks_init_list({ console_sink, file_sink }));
    // spdlog::register_logger(logger);

    // // 设置日志格式
    // spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [thread %t] %v");
    // spdlog::info("This is an informational message");
    // spdlog::error("This is an error message");
    // spdlog::info("Server is starting...");
    // spdlog::info("Server verstion is {}", SeverVersion);
    // spdlog::info("Current libhv version: {}", hv_version());

    // MyWebServer server;
    // server.start();

    // spdlog::shutdown();

    // hv::EventLoopPtr loop(new hv::EventLoop);
    // loop->postEvent([](hv::Event *) {

    // });

    // loop->run();

    spdlog::info("Server is starting...");

    // 启动web线程
    MyWebServer::startWebSever();

    hv::HttpService router;

    // curl -v http://ip:port/
    router.Static("/", "./html");

    // curl -v http://ip:port/proxy/get
    router.Proxy("/proxy/", "http://httpbin.org/");

    // curl -v http://ip:port/test
    router.GET("/test", [](HttpRequest * req, HttpResponse * resp) {
        resp->json["result"] = "ok";
        return 200;
    });

    // curl -v http://ip:port/data
    router.GET("/data", [](HttpRequest * req, HttpResponse * resp) {
        static char data[] = "0123456789";
        return resp->Data(data, 10 /*, false */);
    });

    // curl -v http://ip:port/paths
    router.GET("/paths", [&router](HttpRequest * req, HttpResponse * resp) {
        return resp->Json(router.Paths());
    });

    // curl -v http://ip:port/get?env=1
    router.GET("/get", [](HttpRequest * req, HttpResponse * resp) {
        resp->json["origin"] = req->client_addr.ip;
        resp->json["url"] = req->url;
        resp->json["args"] = req->query_params;
        resp->json["headers"] = req->headers;
        return 200;
    });

    // curl -v http://ip:port/echo -d "hello,world!"
    router.POST("/echo", [](const HttpContextPtr & ctx) {
        return ctx->send(ctx->body(), ctx->type());
    });

    // curl -v http://ip:port/user/123
    router.GET("/user/{id}", [](const HttpContextPtr & ctx) {
        hv::Json resp;
        resp["id"] = ctx->param("id");
        return ctx->send(resp.dump(2));
    });

    http_server_t server;
    server.port = 8080;
    server.service = &router;
    http_server_run(&server);
    return 0;
}
