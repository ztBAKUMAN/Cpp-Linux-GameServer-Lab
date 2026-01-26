#include "Monster.h"

void Goblin::attack()
{
    std::cout << "Goblin Attack" << std::endl;
}

void Goblin::beAttacked(int power)
{
    std::cout << "Goblin was asttacked" << std::endl;
    m_hp -= power;
    if(m_hp <= 0)
    {
        dead();
    }
}

void Goblin::dead()
{
    std::cout << "Goblin is dead" << std::endl;
}


void Boss::attack()
{
    std::cout << "Boss Attack" << std::endl;
}

void Boss::beAttacked(int power)
{
    std::cout << "Boss was asttacked" << std::endl;
    m_hp -= power;
    if(m_hp <= 0)
    {
        dead();
    }
}

void Boss::dead()
{
    std::cout << "Boss is dead" << std::endl;
}