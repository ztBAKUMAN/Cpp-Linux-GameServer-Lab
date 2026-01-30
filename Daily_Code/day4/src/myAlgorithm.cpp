#include "myClass.h"
#include <map>
#include <vector>
#include <algorithm>    // STL算法库

int main()
{
    // 创建编号列表
    std::vector<int> codeList = {1, 2, 3, 4};
    // 创建map容器
    std::map<int, std::unique_ptr<Monster>> monsterData;
    // 创建monster并分配编号
    for(auto num : codeList)
    {
        std::string name = "goblin" + std::to_string(num);
        monsterData.insert(std::make_pair(num, std::make_unique<Monster>(name)));
    }

    // 寻找monster
    auto it = monsterData.find(codeList[1]);
    if(it != monsterData.end())
    {
        auto& tmp = (*it);
        std::cout << "Find monster: " << tmp.second.get()->getName() << std::endl;
    }
    else
    {
        std::cout << "Not Found!" << std::endl;
    }

    
    // 遍历monster设置血量
    std::vector<int> hpVec = {10, 30, 60, 80};
    for(int i = 0; i < codeList.size(); ++i)
    {
        auto it = monsterData.find(codeList[i]);
        if(it != monsterData.end())
        {
            (*it).second.get()->beAttacked(hpVec[i]);
        }
    }
    // 输出剩余血量
    std::for_each(monsterData.begin(), monsterData.end(), [](std::pair<const int, std::unique_ptr<Monster>>& tmp){
        tmp.second->currentHP();
    });
    
    // 检测血量临时函数
    auto isLowHP = [](int n){return (n < 50);};
    // 统计低血量monster数量
    int count = std::count_if(monsterData.begin(), monsterData.end(), [=](std::pair<const int, std::unique_ptr<Monster>>& tmp){
        return isLowHP(tmp.second->getHP());
    });
    std::cout << "共计" << count << "个monster血量过低" << std::endl;

    return 0;
}