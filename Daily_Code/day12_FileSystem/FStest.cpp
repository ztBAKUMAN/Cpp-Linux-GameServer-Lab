#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <iomanip>  // std::put_time
#include <ctime>    // std::localtime

// 设置filesystem简称
namespace fs = std::filesystem;

std::string formatTime(fs::file_time_type fTime)
{
    // 文件时间转换为系统时钟
    auto sTime = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
        fTime - fs::file_time_type::clock::now() + std::chrono::system_clock::now()
    );
    std::time_t cftime = std::chrono::system_clock::to_time_t(sTime);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&cftime), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// 生成本地测试文件
void createTestFile()
{
    std::ofstream("savedata_01.dat") << "SaveData1";
    std::ofstream("savedata_02.dat") << "SaveData2";
    std::ofstream("config.cfg") << "ConfigData";
    std::cout << "Created test files." << std::endl;
}

int main()
{
    // 创建测试文件
    createTestFile();
    // 切换到当前执行目录
    std::string path = "./";
    // 输出目录路径
    std::cout << "Current Path: " << fs::absolute(path) << std::endl;

    try{
        if(!fs::exists(path))
        {
            std::cerr << "path not exists!" << std::endl;
            return 1;
        }
        // 遍历目录
        int count = 0;
        for (const auto& entry : fs::directory_iterator(path))
        {
            // 只输出普通文件且后缀名为dat
            if(entry.is_regular_file() && entry.path().extension() == ".dat")
            {
                count++;
                std::string fName = entry.path().filename().string();
                uintmax_t fSize = fs::file_size(entry);
                auto ftime = fs::last_write_time(entry);
                std::cout << "File " << count << ": " << fName
                          << " | Size: " << fSize << " bytes"
                          << " | Last Modified: " << formatTime(ftime) << std::endl;
            }
        }
        if(count == 0)
        {
            std::cout << "No .dat files found in the directory." << std::endl;
        }
        else
        {
            std::cout << "Total .dat files found: " << count << std::endl;
        }
    }catch(const fs::filesystem_error& e)
    {
        // 发生异常
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}