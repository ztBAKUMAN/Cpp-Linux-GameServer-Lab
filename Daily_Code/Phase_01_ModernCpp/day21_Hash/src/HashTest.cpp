#include "AssetManager.hpp"
#include "AssetKey.hpp"

const int TYPE_TEXTURE = 1;
const int TYPE_SOUND   = 2;

int main()
{
    MyLogger::getInstance().open("MyHash.log");
    LOG_INFO("Hash Test Start");

    AssetKey heroTexture = {TYPE_TEXTURE, 1001};
    AssetKey heroSound   = {TYPE_SOUND,   1001};

    auto tex = AssetManager::getInstance().getAsset(heroTexture);
    auto snd = AssetManager::getInstance().getAsset(heroSound);

    tex->use();
    snd->use();
    
    {
        auto tex2 = AssetManager::getInstance().getAsset(heroTexture);
        LOG_INFO("Tex use count: ", tex.use_count());
    }

    std::hash<AssetKey> hasher;
    LOG_INFO("Hash of heroTexture: ", hasher(heroTexture));
    LOG_INFO("Hash of heroSound:   ", hasher(heroSound));

    LOG_INFO("Hash Test End");
    return 0;
}