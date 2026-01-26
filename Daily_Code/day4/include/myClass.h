#pragma once

#include <iostream>
#include <string>
#include <memory>

class Monster{
public:
    Monster() = delete;
    // 构造函数：初始化列表初始化 hp 和 power
    Monster(std::string n) : m_name(n), m_hp(100), m_power(10){
        std::cout << getName() << "出现" << std::endl;
    }
    
    ~Monster(){
        std::cout << getName() << "消失" << std::endl;
    }
    
    void setMonsterName(const std::string& name){
        m_name = name;
    }
    
    std::string getName() const {return m_name;}
    int getAttackPower() const {return m_power;}
    int getHP() const {return m_hp;}
    
    void attack() const
    {
        std::cout << getName() << "发动攻击！造成" << getAttackPower() << "点伤害" << std::endl;
    }
    
    void beAttacked(int damage)
    {
        m_hp -= damage;
        std::cout << getName() << "被攻击！损失" << damage << "点血量" << std::endl;
    }
    
    void currentHP() const
    {
        std::cout << getName() << "当前剩余" << getHP() << "点血量" << std::endl;
    }

private:
    int m_hp;
    int m_power;
    std::string m_name;
};