#include<sys/ipc.h>
#include <iostream>
#include<boost/interprocess/managed_shared_memory.hpp>
#include<string>
#include <thread>
#include <chrono>
using namespace boost::interprocess;

template<class T>
class SharedMemory
{
public:
    SharedMemory(const std::string & sharedMemName):segment(open_or_create , sharedMemName.c_str(), sizeof(T)*65536)
    {
        std::cout <<"sizeof T:" << sizeof(T)<<"\n";
        data_Addr = segment.construct<T>((sharedMemName + "_dataAddr").c_str())(0);
        this->sharedMemName = sharedMemName;

    }
    void write(const T & data)
    {
        *data_Addr = data;
    }

    T read()
    {
        return *data_Addr;
    }
    ~SharedMemory()
    {
        segment.destroy<T>(sharedMemName.c_str());
    }
private:
    managed_shared_memory segment;
    std::string sharedMemName;
    T* data_Addr;
};

int main(int argc, char const *argv[])
{
    SharedMemory<int> mem("mysadsad");
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        mem.write(20);
        int data = mem.read();
        std::cout << data;
    }

    return 0;
}
