#include<thread>
#include <iostream>

class background_task
{
public:
    void operator()()const
    {
        while(true){
            std::cout <<"1\n";
        }
    }
};

int main()
{
    background_task task1;
    std::thread t1(task1);
    t1.join();
    return 0;
}