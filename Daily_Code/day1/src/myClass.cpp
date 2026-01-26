#include "myClass.h"
#include <mutex>
#include <iostream>

const int g_count = 10;

MyClass::MyClass()
{
    m_num = 0;
    init();
}
MyClass::MyClass(int num) : m_num(num)
{
    init();
}
MyClass::~MyClass()
{

}

void MyClass::coutList()
{
    for(auto num : m_list)
    {
        std::cout << " " << num;
    }
}
void MyClass::setNumList(const std::list<int>& numList)
{
    m_list = numList;
}

void MyClass::init()
{
    m_list.clear();
    for(int i = 0; i < g_count; ++i)
    {
        m_list.push_back(i);
    }
}