#pragma once
#include <iostream>
#include <string>
#include <mutex>
#include <chrono>
#include <ctime>
#include <iomanip>

// 日志等级
enum class LogLevel
{
    EM_DEBUG,
    EM_INFO,
    EM_WARN,
    EM_ERROR
};

class MyLogger
{
public:
    // 获取单例
    static MyLogger &getInstance()
    {
        static MyLogger logger;
        return logger;
    };

    ~MyLogger() = default;

    // **变参模板函数：支持任意数量任意类型
    template <typename... Args>
    void Log(LogLevel level, const char *filename, int line, Args... args)
    {
        std::lock_guard<std::mutex> locker(m_mutex);

        // 打印时间
        auto nowTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "[" << std::put_time(std::localtime(&nowTime), "%H:%M:%S") << "]";

        // 打印日志等级，用不同颜色区分
        // \033[34m表示Linux终端控制符
        switch (level)
        {
        case LogLevel::EM_DEBUG:
            std::cout << "\033[34m[DEBUG]\033[0m ";
            break; // 蓝色
        case LogLevel::EM_INFO:
            std::cout << "\033[32m[INFO]\033[0m ";
            break; // 绿色
        case LogLevel::EM_WARN:
            std::cout << "\033[33m[WARN]\033[0m ";
            break; // 黄色
        case LogLevel::EM_ERROR:
            std::cout << "\033[31m[ERROR]\033[0m ";
            break; // 红色
        default:
            break;
        }

        // 打印实际内容(递归打印剩余参数) C++17折叠表达式实现
        ((std::cout << args << " "), ...);

        // 打印文件和行号
        std::cout << " (" << filename << ":" << line << ")" << std::endl;
    }

private:
    MyLogger() = default;
    MyLogger(const MyLogger &obj) = delete;
    MyLogger &operator=(const MyLogger &obj) = delete;
    std::mutex m_mutex;
};

// 预处理将 __FILE__ 和 __LINE__ 自动替换为文件名和行号
// 使用宏替换避免调用时手动输入固定参数信息
#define LOG_DEBUG(...) MyLogger::getInstance().Log(LogLevel::EM_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) MyLogger::getInstance().Log(LogLevel::EM_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) MyLogger::getInstance().Log(LogLevel::EM_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) MyLogger::getInstance().Log(LogLevel::EM_ERROR, __FILE__, __LINE__, __VA_ARGS__)