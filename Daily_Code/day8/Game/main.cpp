#include "Monster.h"
#include <memory>
#include <vector>

int main()
{
    // 创建抽象类类型的独占指针集合
    std::vector<std::unique_ptr<Monster>> monsterGroup;
    // 抽象父类指针指向子类
    std::unique_ptr<Monster> goblin = std::make_unique<Goblin>("goblin");
    std::unique_ptr<Monster> boss   = std::make_unique<Boss>("boss");
    monsterGroup.push_back(std::move(goblin));
    monsterGroup.push_back(std::move(boss));
    // 调用同一接口函数，完成不同实现
    for(const auto& it : monsterGroup)
    {
        it->attack();
    }
    return 0;
}