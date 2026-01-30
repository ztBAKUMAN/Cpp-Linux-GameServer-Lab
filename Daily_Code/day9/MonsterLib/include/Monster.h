#pragma once
#include <iostream>
#include <string>
#include <memory>

//** 使用PImpl模式：净化头文件，封装数据，避免链式编译 **//

// 抽象基类
class Monster
{
public:
    // 指定构造函数必须带string参数
    Monster() = delete;
    explicit Monster(std::string name);
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
    virtual void beAttacked(int power);
    virtual void dead() = 0;

protected:
    // Getter
    std::string getName() const;
    int getHp() const;
    // Setter
    void setName(const std::string& name);
    void setHp(int hp);

private:
    struct Impl;                      // 前置声明Impl结构体, 用来存放私有数据
    std::unique_ptr<Impl> m_pImpl;    // PImpl指针
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