#include "Monster.h"

Monster::~Monster()
{
    std::cout << "Monster " << m_name << " is destroyed" << std::endl;
    if(m_leakPtr != nullptr)
    {
        delete m_leakPtr;
        m_leakPtr = nullptr;
    }
}
Monster::Monster(const Monster& obj)
{
    m_name = obj.m_name;
    m_hp = obj.m_hp;
    // 独占指针手动make_unique
    if(obj.m_uptr)
    {
        m_uptr = std::make_unique<int>(*(obj.m_uptr));
    }
    else
    {
        m_uptr.reset();
    }
    // 共享指针直接赋值
    m_sptr = obj.m_sptr;

    // 浅拷贝
    // m_leakPtr = obj.m_leakPtr;
    // 深拷贝
    if(obj.m_leakPtr)
    {
        m_leakPtr = new int;
        *m_leakPtr = *(obj.m_leakPtr);
    }
    else
    {
        m_leakPtr = nullptr;
    }
}

Monster& Monster::operator=(const Monster& obj)
{
    // 是否自赋值
    if(this != &obj)
    {
        m_name = obj.m_name;
        m_hp = obj.m_hp;
        
        if(obj.m_uptr)
        {
            m_uptr = std::make_unique<int>(*(obj.m_uptr));
        }
        else
        {
            m_uptr.reset();
        }

        m_sptr = obj.m_sptr;

        // 裸指针必须先释放自身
        delete m_leakPtr;

        if(obj.m_leakPtr)
        {
            m_leakPtr = new int;
            *m_leakPtr = *(obj.m_leakPtr);
        }
        else
        {
            m_leakPtr = nullptr;
        }
    }
    return *this;
}

Monster::Monster(Monster&& obj) noexcept
{
    m_hp = obj.m_hp;
    // 使用move语义转移资源
    m_name = std::move(obj.m_name);
    m_uptr = std::move(obj.m_uptr);
    m_sptr = std::move(obj.m_sptr);

    // 拿到对方地址
    m_leakPtr = obj.m_leakPtr;
    // 置空对方地址，防止析构时释放两次
    obj.m_leakPtr = nullptr;
}

Monster& Monster::operator=(Monster&& obj) noexcept
{
    // 是否自赋值
    if(this != &obj)
    {
        m_hp = obj.m_hp;
        m_name = std::move(obj.m_name);
        m_uptr = std::move(obj.m_uptr);
        m_sptr = std::move(obj.m_sptr);

        // 裸指针必须先释放自身
        delete m_leakPtr;
        // 拿到对方地址
        m_leakPtr = obj.m_leakPtr;
        // 置空对方地址，防止析构时释放两次
        obj.m_leakPtr = nullptr;
    }
    return *this;
}

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