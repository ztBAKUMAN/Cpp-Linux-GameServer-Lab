#include "Monster.h"

void Goblin::attack()
{
    std::cout << "Goblin Attack" << std::endl;
}

void Goblin::dead()
{
    std::cout << "Goblin is dead" << std::endl;
}


void Boss::attack()
{
    std::cout << "Boss Attack" << std::endl;
}

void Boss::dead()
{
    std::cout << "Boss is dead" << std::endl;
}