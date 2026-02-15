#include "MyLogger.hpp"
#include <vector>
#include <thread>

// 线程工作函数
void franticWorker(int id) {
    for(int i=0; i<1000; ++i) {
        LOG_INFO("Thread ", id, " message ", i);
    }
}

int main() {
    LOG_INFO("AsyncTest Start...");

    // 启动 4 个线程写日志
    std::vector<std::thread> threads;
    for(int i=0; i<4; ++i) {
        threads.emplace_back(franticWorker, i);
    }

    for(auto& t : threads) t.join();

    LOG_INFO("AsyncTest End!");
    return 0;
}