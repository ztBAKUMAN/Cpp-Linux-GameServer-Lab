#include "Monster.h"
#include <memory>
#include <vector>
#include <algorithm>

int main()
{
    // 创建抽象类类型的独占指针集合
    std::vector<std::unique_ptr<Monster>> monsterArmy;
    monsterArmy.emplace_back(std::make_unique<Goblin>("Goblin_A"));
    monsterArmy.emplace_back(std::make_unique<Goblin>("Goblin_B"));
    monsterArmy.emplace_back(std::make_unique<Boss>("Dragon_Boss"));

    // 排序，HP从高到低
    std::sort(monsterArmy.begin(), monsterArmy.end(),
                [](const std::unique_ptr<Monster>& a, const std::unique_ptr<Monster>& b) {
                    // 前一个比后一个HP高则返回true
                    return a->getHp() > b->getHp();
                });

    // 遍历对象调用attack和beAttacked方法
    std::for_each(monsterArmy.begin(), monsterArmy.end(),
                    [](const std::unique_ptr<Monster>& monster){
                        monster->attack();
                        monster->beAttacked(100);
                    });

    // 寻找Boss
    auto it = std::find_if(monsterArmy.begin(), monsterArmy.end(),
                            [](const std::unique_ptr<Monster>& monster){
                                // 名称判断法
                                // return monster->getName() == "Dragon_Boss";
                                // 粗略判断法
                                // return monster->getName().find("Boss") != std::string::npos;

                                // typeid判断法，需包含 <typeinfo> 头文件
                                // 限制: 类型必须严格相等
                                // return typeid(*(monster.get())) == typeid(Boss); 
                                // 或 return typeid(*monster) == typeid(Boss);

                                // dynamic_cast判断法
                                // 优势: 支持子类类型判断
                                return dynamic_cast<Boss*>(monster.get()) != nullptr;
                            });

    // 找到Boss对其进行攻击
    if(it != monsterArmy.end())
    {
        (*it)->beAttacked(500);
    }

    // 判断HP，删除死亡对象
    auto deadObjects = std::remove_if(monsterArmy.begin(), monsterArmy.end(),
                                [](const std::unique_ptr<Monster>& monster){
                                    return monster->isDead();
                                });
    // 删除真实对象，释放内存，容器缩小
    monsterArmy.erase(deadObjects, monsterArmy.end());

    // 打印HP
    for(const auto& monster : monsterArmy)
    {
        std::cout << "Monster " << monster->getName() << " has hp: " << monster->getHp() << std::endl;
    }
                    
    return 0;
}