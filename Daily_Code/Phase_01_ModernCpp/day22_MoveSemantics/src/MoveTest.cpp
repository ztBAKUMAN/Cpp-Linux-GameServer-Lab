#include "HeavyAsset.hpp"
#include <vector>

HeavyAsset LoadHugeModel() {
    LOG_INFO("--- Inside LoadHugeModel ---");
    HeavyAsset temp(100 * 1024 * 1024, "Qwen_1.5B_Model");
    return temp; 
}

int main() {
    MyLogger::getInstance().open("move_test.log");
    LOG_INFO("=== Move Semantics Test Start ===");

    {
        HeavyAsset asset1(50 * 1024 * 1024, "Level_1_Map");

        // 强制深拷贝
        LOG_INFO("\n--- Triggering Deep Copy ---");
        HeavyAsset asset2 = asset1; // 调用拷贝构造函数

        // 强制移动 (转移所有权)
        LOG_INFO("\n--- Triggering Move ---");
        HeavyAsset asset3 = std::move(asset1); 
    }

    LOG_INFO("\n--- Function Return Test ---");
    HeavyAsset myModel = LoadHugeModel();

    LOG_INFO("=== Test End ===");
    return 0;
}