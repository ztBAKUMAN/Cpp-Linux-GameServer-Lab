#include "ScopedTimer.hpp"
#include <thread>
#include <vector>

// 宏定义：利用 __LINE__ 和 ## 生成唯一的变量名，调用时自动生成对象名
// ！注意：使用粘合符##时，参数不会展开！所以要与__LINE__分开使用
#define CONCAT(a, b) a##b   // 3.合并参数
#define UNIQUE_NAME(prefix, line) CONCAT(prefix, line)  // 2.展开__LINE__
#define SCOPED_TIMER(name) ScopedTimer UNIQUE_NAME(timer_, __LINE__)(name)  // 1.调用对象

// 线程睡眠
void FunctionSleep()
{
    SCOPED_TIMER("FunctionSleep");
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    LOG_INFO("sleep for 200ms");
}

// 循环
void FunctionLoop()
{
    SCOPED_TIMER("FunctionLoop");
    long count = 0;
    for(int i = 0; i < 10000000; ++i)
    {
        count++;
    }
    LOG_INFO("loop count ", count);
}

int main() {
    LOG_INFO("Start Timer Test...");

    // 记录普通函数耗时
    FunctionSleep();
    FunctionLoop();

    // 记录局部函数耗时
    {
        SCOPED_TIMER("BlockScope");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        LOG_INFO("sleep for 100ms");
    }

    LOG_INFO("Timer Test Finished!");
    return 0;
}