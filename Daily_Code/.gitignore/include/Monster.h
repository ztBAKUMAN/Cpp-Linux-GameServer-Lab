#include <iostream>
#include <string>

class Monster
{
public:
    Monster() = delete;
    explicit Monster(std::string name) {
        m_name = name;
    }
    virtual ~Monster() = default;

    virtual void attack() = 0;
    virtual void beAttacked(int) = 0;
    virtual void dead() = 0;

protected:
    int m_hp{100};
    std::string m_name;
};

class Goblin : public Monster
{
public:
    using Monster::Monster;
    virtual ~Goblin(){}

    virtual void attack () override;
    virtual void beAttacked (int) override;
    virtual void dead () override;
};

class Boss : public Monster
{
public:
    using Monster::Monster;
    virtual ~Boss(){}

    virtual void attack () override;
    virtual void beAttacked (int) override;
    virtual void dead () override;
};