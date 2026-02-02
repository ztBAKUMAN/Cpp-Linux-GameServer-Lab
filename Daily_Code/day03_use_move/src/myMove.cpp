#include "myMove.h"
#include <vector>

int main()
{
    // 尝试值拷贝独占指针
    auto mon1 = std::make_unique<Monster>("goblin");
    // auto mon2 = mon1;
    // 转移goblin独占权限，所有权从指针mon1转到指针mon2
    auto mon2 = std::move(mon1);
    // 验证mon1是否存在
    if(mon1 == nullptr)
    {
        std::cout << "goblin独占权已转移" << std::endl;
    }
    mon2->attack();

    // 创建不同容器
    std::vector<std::unique_ptr<Monster>> army_unique;
    std::vector<Monster> army_copy;
    std::vector<Monster*> army_ptr;
    // 无法创建引用类型的vector
    // std::vector<Monster&> army_ref;

    // 创建dragon独占指针
    auto dragon_ptr = std::make_unique<Monster>("dragon");
    // 将dragon_ptr解引用并赋值给实体对象
    Monster dragon_obj = *dragon_ptr.get();
    // 初始血量100
    dragon_ptr->currentHP();
    army_unique.push_back(std::move(dragon_ptr));   // 不能直接放入vector，不然会触发拷贝
    // army_copy.push_back(*dragon_ptr.get());  // dragon_ptr已变为空指针，不能解引用
    // army_ptr.push_back(dragon_ptr.get());  // dragon_ptr已变为空指针，不能解引用
    army_copy.push_back(*army_unique.front().get());
    army_ptr.push_back(army_unique.front().get());

    
    army_unique.front()->beAttacked(10);
    // 查看每个成员血量是否同步
    dragon_obj.currentHP();
    army_unique.front()->currentHP();
    army_copy.front().currentHP();
    army_ptr.front()->currentHP();
    return 0;
}