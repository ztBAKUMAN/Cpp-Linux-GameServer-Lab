#pragma once
#include <iostream>
#include <string>
#include <memory>

// 抽象基类
class Monster
{
public:
    // 指定构造函数必须带string参数
    Monster() = delete;
    explicit Monster(std::string name) {
        m_name = name;
    }
    // 虚析构保证子类调用析构
    virtual ~Monster();

    /* 自定义构造函数 */
    // 拷贝构造
    Monster(const Monster& obj);
    // 赋值构造
    Monster& operator=(const Monster& obj);
    // 拷贝移动
    Monster(Monster&& obj) noexcept;
    // 赋值移动
    Monster& operator=(Monster&& obj) noexcept;

    // 纯虚函数强制子类实现
    virtual void attack() = 0;
    // 虚函数允许子类不用重写
    virtual void beAttacked(int power) {
        std::cout << m_name << "was asttacked" << std::endl;
        m_hp -= power;
        if(m_hp <= 0)
        {
            dead();
        }
    }
    virtual void dead() = 0;

protected:
    int m_hp{100};
    std::string m_name;
    std::unique_ptr<int> m_uptr;    // 独占指针
    std::shared_ptr<int> m_sptr;    // 共享指针
    int* m_leakPtr{nullptr};        // 裸指针
};

class Goblin : public Monster
{
public:
    using Monster::Monster;
    virtual ~Goblin() = default;

    virtual void attack () override;
    virtual void dead () override;
};

class Boss : public Monster
{
public:
    using Monster::Monster;
    virtual ~Boss() = default;

    virtual void attack () override;
    virtual void dead () override;
};