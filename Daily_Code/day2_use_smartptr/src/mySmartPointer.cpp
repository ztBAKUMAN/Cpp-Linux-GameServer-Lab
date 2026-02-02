#include "mySmartPointer.h"

void createMonsterByUnique(std::string name)
{
    auto monster = std::make_unique<Monster>(name);
}

void teamAttack(const Monster& m)
{
    m.attack();
}

void teamAttack(Monster* m)
{
    m->attack();
}

int main()
{
    // 独占指针创建Goblin
    createMonsterByUnique("Goblin Boss");

    // 共享指针创建Goblin
    auto monster = std::make_shared<Monster>("Goblin NPC");

    std::cout << "Goblin NPC数量: " << monster.use_count() << std::endl;
    // 引用调用
    teamAttack(*monster.get());
    // 指针调用
    teamAttack(monster.get());
    std::cout << "Goblin NPC数量: " << monster.use_count() << std::endl;

    return 0;
}