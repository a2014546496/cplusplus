#include<thread>
#include <iostream>


int main()
{
    std::unique_ptr<std::string> ptr(new std::string("123456"));
    std::unique_ptr<std::string> temp = std::move(ptr);
    std::cout <<*temp;
    std::cout << int(ptr == nullptr);
    return 0;
}