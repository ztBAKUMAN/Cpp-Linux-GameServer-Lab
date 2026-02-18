#pragma once
#include "MyLogger.hpp"
#include "AssetKey.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

class Asset
{
public:
    explicit Asset(const AssetKey& key) : m_key(key){
        LOG_INFO("[Asset] Loaded: ", m_key);
    }
    ~Asset(){
        LOG_INFO("[Asset] Destroyed: ", m_key);
    }
    void use() const {
        LOG_INFO("Using: ", m_key);
    }
private:
    AssetKey m_key;
};

class AssetManager
{
public:
    static AssetManager& getInstance()
    {
        static AssetManager ins;
        return ins;
    }

    std::shared_ptr<Asset> getAsset(const AssetKey& key)
    {
        auto it = m_cache.find(key);
        if(it != m_cache.end())
        {
            std::shared_ptr<Asset> sharedAsset = it->second.lock();
            if(sharedAsset)
            {
                LOG_INFO("[Manager] Returning existing asset: ", key);
                return sharedAsset;
            }
            else
            {
                LOG_DEBUG("[Manager] Cache expired!");
                m_cache.erase(it);
            }
        }

        LOG_INFO("[Manager] Loading new asset...");
        std::shared_ptr<Asset> newAsset = std::make_shared<Asset>(key);
        m_cache[key] = newAsset;
        return newAsset;
    }
private:
    AssetManager() = default;
    AssetManager(const AssetManager& obj) = delete;
    AssetManager& operator=(const AssetManager& obj) = delete;

    std::unordered_map<AssetKey, std::weak_ptr<Asset>> m_cache;
};