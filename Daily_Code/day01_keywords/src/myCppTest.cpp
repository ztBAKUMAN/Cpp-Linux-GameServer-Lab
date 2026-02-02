#include <iostream>
#include "myClass.h"

int main()
{
    std::cout << "Hello World!" << std::endl;
    
    int num = 0;
    const int* p1 = &num;
    int* const p2 = &num;
    // *p1 = 1; // 不能改变指向地址的值
    *p2 = ++num;
    p1 = p2;
    // p2 = p1; // 不能指向其他地址
    std::cout << "num: " << *p1 << std::endl;

    // 实例化myclass
    MyClass c(123);
    std::cout << "classNum: " << c.getMyClassNum() << std::endl;
    c.coutList();

    return 0;
}