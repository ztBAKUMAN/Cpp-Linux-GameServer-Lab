#include "MyLogger.hpp"
#include <thread>
#include <vector>

// 模拟工作函数
void worker(int id) {
    LOG_INFO("Current Thread ID: ", id);
    LOG_DEBUG("Test...");
    if (id % 2 == 0) {
        LOG_WARN("Worker", id, "Warning!");
    } else {
        LOG_ERROR("Worker", id, "Error!");
    }
}

int main() {
    LOG_INFO("Start...");

    // 测试多线程安全性
    std::vector<std::thread> threads;
    for(int i=0; i<5; ++i) 
    {
        threads.emplace_back(worker, i);
    }

    for(auto& t : threads) t.join();

    LOG_INFO("All Ready!!");
    return 0;
}