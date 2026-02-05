#pragma once
#include <string>
#include <vector>

// 配置文件结构体
struct JsonConfig{
    std::string ip;
    int port;
    int maxPlayer;
    bool pvp;
    std::vector<int> loginID;

    // JsonConfig& operator=(const JsonConfig& obj){
    //         if(&obj != this)
    //         {
    //             ip = obj.ip;
    //             port = obj.port;
    //             maxPlayer = obj.maxPlayer;
    //             pvp = obj.pvp;
    //             loginID = obj.loginID;
    //         }
    //         return *this;
    // }
};