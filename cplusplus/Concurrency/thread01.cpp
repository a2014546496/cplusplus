#include<thread>
#include <iostream>

void fun()
{

    std::cout << "111";
}
int main()
{
    std::thread t1(fun);
    t1.join();
    return 0;
}