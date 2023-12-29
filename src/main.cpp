#include <hv/hloop.h>
#include <iostream>
#include <vector>
#include <hv/HttpServer.h>
#include <spdlog/spdlog.h>
using namespace std;

// 定时器回调函数
static void
on_timer(htimer_t * timer)
{
    printf("time=%lus\n", (unsigned long)time(NULL));
}

int
main()
{
    // 新建一个事件循环结构体
    hloop_t * loop = hloop_new(0);

    // 添加一个定时器
    htimer_add(loop, on_timer, 1000, INFINITE);

    // 运行事件循环
    hloop_run(loop);

    // 释放事件循环结构体
    hloop_free(&loop);
    return 0;
}
