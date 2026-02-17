#pragma once
#include "MyLogger.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

class Asset
{
public:
    explicit Asset(const std::string& name) : m_name(name){
        LOG_INFO("[Asset] Loaded: ", name);
    }
    ~Asset(){
        LOG_INFO("[Asset] Destroyed: ", m_name);
    }
    void use() const {
        LOG_INFO("Using: ", m_name);
    }
private:
    std::string m_name;
};

class AssetManager
{
public:
    static AssetManager& getInstance()
    {
        static AssetManager ins;
        return ins;
    }

    std::shared_ptr<Asset> getAsset(const std::string& name)
    {
        auto it = m_cache.find(name);
        if(it != m_cache.end())
        {
            std::shared_ptr<Asset> sharedAsset = it->second.lock();
            if(sharedAsset)
            {
                LOG_INFO("[Manager] Returning existing asset: ", name);
                return sharedAsset;
            }
            else
            {
                LOG_DEBUG("[Manager] Cache expired!");
            }
        }

        LOG_INFO("[Manager] Loading new asset...");
        std::shared_ptr<Asset> newAsset = std::make_shared<Asset>(name);
        m_cache[name] = newAsset;
        return newAsset;
    }
private:
    AssetManager() = default;
    AssetManager(const AssetManager& obj) = delete;
    AssetManager& operator=(const AssetManager& obj) = delete;

    std::unordered_map<std::string, std::weak_ptr<Asset>> m_cache;
};