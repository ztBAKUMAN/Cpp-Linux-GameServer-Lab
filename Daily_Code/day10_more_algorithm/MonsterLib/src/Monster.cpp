#include "Monster.h"

struct Monster::Impl
{
    int m_hp{100};
    int m_power{10};
    std::string m_name;

    std::unique_ptr<int> m_uptr;    // 独占指针
    std::shared_ptr<int> m_sptr;    // 共享指针
    int* m_leakPtr{nullptr};        // 裸指针

    Impl() = default;
    // 实现Impl的拷贝构造函数
    Impl(const Impl& obj)
        :m_hp(obj.m_hp),
         m_power(obj.m_power),
         m_name(obj.m_name),
         m_sptr(obj.m_sptr)
    {
        // 裸指针深拷贝
        if(obj.m_leakPtr != nullptr)
        {
            m_leakPtr = new int(*obj.m_leakPtr);
        }
        else
        {
            m_leakPtr = nullptr;
        }
        // 独占指针深拷贝
        if(obj.m_uptr)
        {
            m_uptr = std::make_unique<int>(*(obj.m_uptr));
        }
        else
        {
            m_uptr.reset();
        }
    }

    // 实现Impl的赋值构造函数
    Impl& operator=(const Impl& obj)
    {
        if(this != &obj)
        {
            m_hp = obj.m_hp;
            m_power = obj.m_power;
            m_name = obj.m_name;
            m_sptr = obj.m_sptr;    
            // 裸指针深拷贝
            delete m_leakPtr;
            if(obj.m_leakPtr != nullptr)
            {
                m_leakPtr = new int(*obj.m_leakPtr);
            }
            else
            {
                m_leakPtr = nullptr;
            }
            // 独占指针深拷贝
            if(obj.m_uptr)
            {
                m_uptr = std::make_unique<int>(*(obj.m_uptr));
            }
            else
            {
                m_uptr.reset();
            }
        }
        return *this;
    }

    ~Impl()
    {
        if(m_leakPtr != nullptr)
        {
            delete m_leakPtr;
            m_leakPtr = nullptr;
        }
    }
};

Monster::Monster(std::string name)
    :m_pImpl(std::make_unique<Impl>())
{
    m_pImpl->m_name = name;
    std::cout << "Monster " << m_pImpl->m_name << " is created" << std::endl;
}

Monster::Monster(std::string name, int hp, int power)
    :m_pImpl(std::make_unique<Impl>())
{
    m_pImpl->m_name = name;
    m_pImpl->m_hp = hp;
    m_pImpl->m_power = power;
    std::cout << "Monster " << m_pImpl->m_name << " is created with hp: " << hp << " and power: " << power << std::endl;
}

Monster::~Monster()
{
    // 使用m_pImpl前必须判断是否存在
    if(m_pImpl)
    {
        std::cout << "Monster " << m_pImpl->m_name << " is destroyed" << std::endl;
    }
    else
    {
        std::cout << "Monster is destroyed" << std::endl;
    }
}

Monster::Monster(const Monster& obj)
{
    // Impl内部已经实现拷贝构造, 所以只需实现m_pImpl的拷贝
    m_pImpl = std::make_unique<Impl>(*(obj.m_pImpl));
}

Monster& Monster::operator=(const Monster& obj)
{
    // 是否自赋值
    if(this != &obj)
    {
        // Impl内部已经实现赋值构造, 所以只需实现m_pImpl的赋值
        *m_pImpl = *(obj.m_pImpl);
    }
    return *this;
}

Monster::Monster(Monster&& obj) noexcept = default;

Monster& Monster::operator=(Monster&& obj) noexcept = default;

std::string Monster::getName() const
{
    return m_pImpl->m_name;
}

int Monster::getHp() const
{
    return m_pImpl->m_hp;
}

int Monster::getPower() const
{
    return m_pImpl->m_power;
}

void Monster::setName(const std::string& name)
{
    m_pImpl->m_name = name;
}

void Monster::setHp(int hp)
{
    m_pImpl->m_hp = hp;
}

void Monster::setPower(int power)
{
    m_pImpl->m_power = power;
}

void Monster::beAttacked(int power)
{
    m_pImpl->m_hp -= power;
    std::cout << "Monster " << m_pImpl->m_name << " is attacked, hp: " << m_pImpl->m_hp << std::endl;
    if(m_pImpl->m_hp <= 0)
    {
        dead();
    }
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