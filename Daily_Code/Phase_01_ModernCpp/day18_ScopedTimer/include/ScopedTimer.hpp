#pragma once
#include "MyLogger.hpp"
#include <chrono>

// 高精度计时器
using HighClock = std::chrono::high_resolution_clock;
class ScopedTimer{
public:
    explicit ScopedTimer(std::string name) : m_name(name), m_start(HighClock::now())
    {
        // 构造时自动记录当前时刻
    }
    ~ScopedTimer()
    {
        // 析构时自动打印时间差
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(HighClock::now() - m_start).count();
        LOG_INFO("[TIMER]", m_name, "took", duration, "ms");
    }

private:
    std::string m_name;
    std::chrono::time_point<HighClock> m_start; // 记录时刻
};