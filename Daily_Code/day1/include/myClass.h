#pragma once
#include <list>

class MyClass{
public:
    MyClass();
    MyClass(int num);
    ~MyClass();

    inline int getMyClassNum() const {return m_num;}
    void setNumList(const std::list<int>& numList);
    void coutList();

private:
void init();
private:
    int m_num;
    std::list<int> m_list;
};