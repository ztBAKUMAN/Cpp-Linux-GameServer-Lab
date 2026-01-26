#include "MyMonster.h"

MyMonster::MyMonster(std::string n) : m_name(n), m_hp(100), m_power(10){
    std::cout << getName() << "出现" << std::endl;
}

MyMonster::~MyMonster()
{
    std::cout << getName() << "消失" << std::endl;
}

void MyMonster::setMonsterName(const std::string& name)
{
    m_name = name;
}

void MyMonster::attack() const
{
    std::cout << getName() << "发动攻击！造成" << getAttackPower() << "点伤害" << std::endl;
}

void MyMonster::beAttacked(int damage)
{
    m_hp -= damage;
    std::cout << getName() << "被攻击！损失" << damage << "点血量" << std::endl;
}

void MyMonster::currentHP() const
{
    std::cout << getName() << "当前剩余" << getHP() << "点血量" << std::endl;
}