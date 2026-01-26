#pragma once

#include <iostream>
#include <string>
#include <memory>

class MyMonster{
public:
    MyMonster() = delete;
    // 构造函数：初始化列表初始化 hp 和 power
    MyMonster(std::string);
    
    ~MyMonster();
    
    void setMonsterName(const std::string&);
    
    inline std::string getName() const {return m_name;}
    inline int getAttackPower() const {return m_power;}
    inline int getHP() const {return m_hp;}
    
    void attack() const;
    void beAttacked(int);
    
    void currentHP() const;

private:
    int m_hp;
    int m_power;
    std::string m_name;
};