#pragma once
#include <iostream>
#include <cstring> 
#include "MyLogger.hpp"

class HeavyAsset {
public:
    // 默认构造函数
    explicit HeavyAsset(size_t size, const std::string& name) 
        : m_size(size), m_name(name) 
    {
        m_data = new char[m_size];
        LOG_INFO("[HeavyAsset] Allocated ", m_size, " bytes for ", m_name);
    }

    // 析构函数
    ~HeavyAsset() {
        if (m_data != nullptr) {
            LOG_INFO("[HeavyAsset] Freeing memory for ", m_name);
            delete[] m_data;
            m_data = nullptr;
        } else {
            LOG_INFO("[HeavyAsset] Destroyed an empty/moved asset: ", m_name);
        }
    }

    // 拷贝构造函数
    HeavyAsset(const HeavyAsset& other) 
        : m_size(other.m_size), m_name(other.m_name + "_copy") 
    {
        LOG_WARN("[HeavyAsset] Deep Copying ", m_size, " bytes from ", other.m_name);
        m_data = new char[m_size];
        std::memcpy(m_data, other.m_data, m_size);
    }

    // 移动构造函数
    HeavyAsset(HeavyAsset&& other) noexcept 
        : m_size(other.m_size), m_name(other.m_name + "_moved") 
    {
        LOG_INFO("[HeavyAsset] Moving (Zero-Copy) from ", other.m_name);
        
        m_data = other.m_data; 

        other.m_data = nullptr; 
        other.m_size = 0;
    }

    HeavyAsset& operator=(const HeavyAsset&) = delete;
    HeavyAsset& operator=(HeavyAsset&&) = delete;

private:
    char* m_data;       // 指向巨量数据的指针
    size_t m_size;      // 数据大小
    std::string m_name; // 资源名称
};