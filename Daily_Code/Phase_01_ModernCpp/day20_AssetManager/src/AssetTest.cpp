#include "AssetManager.hpp"

void simulatePlayerA() 
{
    LOG_INFO("Player A enters game");

    auto armor = AssetManager::getInstance().getAsset("iron_armor.png");
    
    armor->use();
}

int main()
{
    LOG_INFO("Game start");

    LOG_INFO("test 1:");
    simulatePlayerA();

    
    LOG_INFO("test 2:");
    {
        auto player_1 = AssetManager::getInstance().getAsset("iron_armor.png");
        auto player_2 = AssetManager::getInstance().getAsset("iron_armor.png");
        LOG_INFO("Reference count: ", player_1.use_count());
    }

    LOG_INFO("test 3:");
    {
        auto player_3 = AssetManager::getInstance().getAsset("iron_armor.png");
        auto player_4 = AssetManager::getInstance().getAsset("gold_armor.png");
    }

    LOG_INFO("Game over");
    return 0;
}