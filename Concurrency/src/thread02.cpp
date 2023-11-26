#include<thread>
#include<iostream>
#include <vector>
#include<utility>


class joining_thread
{
    std::thread t;
public:
    joining_thread() noexcept=default;
    template<typename Callable, typename ... Args>
    explicit joining_thread(Callable && func, Args&& ... args):
        t(std::forward<Callable>(func), std::forward<Args>(args) ...)
    {}

    explicit joining_thread(std::thread t_) noexcept:
    t(std::move(t_))
    {}

    joining_thread(joining_thread&& other) noexcept:
        t(std::move(other.t))
    {}

    joining_thread & operator = (joining_thread && other) noexcept
    {
        if(joinable())
            join();
        
        t= std::move(other);

        return *this;
    }

    joining_thread & operator = (std::thread ohter) noexcept   
    {
        if(joinable())
            join();
        
        t= std::move(other);
        return *this;
    }
    
    ~joining_thread() noexcept
    {
        if(joinable())
            join();
    }
    
    std::thread::id get_id() const noexcept {
        return t.get_id();
    }

    bool joinable() const noexcept
    {
        return t.joinable();
    }

    void join()
    {
        t.join();
    }

    void detach()
    {
        t.detach();
    }

    std::thread& as_thread() noexcept
    {
        return t;
    }

    const std::thread & as_thread() const noexcept
    {
        return t;
    }
}; 

void do_work(unsigned id)
{
    std::cout << id<<"\n";
}

int main()
{
    std::vector<std::thread> threads;
    for(unsigned i = 0; i < 20; i++)
    {
        threads.push_back(std::thread(do_work, i));
    }

    for(auto & it : threads)
    {
        it.join();
    }

    return 0;
}