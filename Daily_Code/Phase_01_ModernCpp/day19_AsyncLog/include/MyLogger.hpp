#pragma once
#include <iostream>
#include <string>
#include <mutex>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <queue>
#include <thread>
#include <condition_variable>

// 日志等级
enum class LogLevel
{
    EM_DEBUG,
    EM_INFO,
    EM_WARN,
    EM_ERROR
};

const std::string defaulFile = "server.log";

class MyLogger
{
public:
    // 获取单例
    static MyLogger &getInstance()
    {
        static MyLogger logger;
        return logger;
    };

    ~MyLogger()
    {
        // 析构时关闭文件
        if(m_logFile.is_open())
        {
            // 刷新缓冲, 确保最后日志写入
            m_logFile.flush();
            m_logFile.close();
        }
    }

    // 打开文件
    void open(const std::string& filename)
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        if(m_logFile.is_open())
        {
            m_logFile.close();
        }
        // 以追加模式打开
        m_logFile.open(filename, std::ios::out | std::ios::app);
        if(!m_logFile.is_open())
        {
            std::cerr << "Failed to open logFile: " << filename << std::endl;
        }
    }

    // **变参模板函数：支持任意数量任意类型
    template <typename... Args>
    void Log(LogLevel level, const char *filename, int line, Args... args)
    {
        std::lock_guard<std::mutex> locker(m_mutex);

        // 打印时间
        auto nowTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::stringstream ss;
        ss << "[" << std::put_time(std::localtime(&nowTime), "%H:%M:%S") << "]";
        std::string timeString = ss.str();

        // 打印日志等级，用不同颜色区分
        // \033[34m表示Linux终端控制符
        const char* levelString = "";
        const char* colorString = "";
        switch (level)
        {
        case LogLevel::EM_DEBUG:
            levelString = "[DEBUG]"; colorString = "\033[34m";
            break; // 蓝色
        case LogLevel::EM_INFO:
            levelString = "[INFO]"; colorString = "\033[32m";
            break; // 绿色
        case LogLevel::EM_WARN:
            levelString = "[WARN]"; colorString = "\033[33m";
            break; // 黄色
        case LogLevel::EM_ERROR:
            levelString = "[ERROR]"; colorString = "\033[31m";
            break; // 红色
        default:
            break;
        }
    
        std::cout << timeString << " " << colorString << levelString << "\033[0m ";
        // 打印实际内容(递归打印剩余参数) C++17折叠表达式实现
        ((std::cout << args << " "), ...);
        // 打印文件和行号
        std::cout << " (" << filename << ":" << line << ")" << std::endl;

        // 将日志写入文件
        if(m_logFile.is_open())
        {
            m_logFile << timeString << " " << levelString << " ";
            ((m_logFile << args << " "), ...);
            m_logFile << " (" << filename << ":" << line << ")" << std::endl;

            // *如果发生ERROR, 刷新缓冲区
            if(level == LogLevel::EM_ERROR)
            {
                m_logFile.flush();
            }
        }
    }

private:
    MyLogger()
    {
        open(defaulFile);
    }
    MyLogger(const MyLogger &obj) = delete;
    MyLogger &operator=(const MyLogger &obj) = delete;

    std::mutex m_mutex;         // 保护logFile
    std::ofstream m_logFile;    // 日志文件
    // 异步成员
    std::mutex m_queueMutex;    // 保护日志队列
    std::condition_variable m_cv;   // 条件变量(信号)
};

// 预处理将 __FILE__ 和 __LINE__ 自动替换为文件名和行号
// 使用宏替换避免调用时手动输入固定参数信息
#define LOG_DEBUG(...) MyLogger::getInstance().Log(LogLevel::EM_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) MyLogger::getInstance().Log(LogLevel::EM_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) MyLogger::getInstance().Log(LogLevel::EM_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) MyLogger::getInstance().Log(LogLevel::EM_ERROR, __FILE__, __LINE__, __VA_ARGS__)