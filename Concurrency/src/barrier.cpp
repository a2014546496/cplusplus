#include <boost/thread/barrier.hpp>
#include<boost/thread/thread.hpp>
#include <iostream>

int main(int argc, char const *argv[])
{
    const int n_threads = 4;
    boost::barrier barrier(n_threads);

    for(int i = 0; i < n_threads; i++) {
        boost::thread([&barrier](){
            std::cout <<boost::this_thread::get_id()<<" arrived\n";
            barrier.wait();
            boost::this_thread::get_id();
            std::cout <<boost::this_thread::get_id()<<" ok\n";
        });
    }
    boost::this_thread::sleep_for(boost::chrono::seconds(2));
    return 0;
}
