#include<iostream>
#include<thread>
#include<chrono>
#include<atomic>

#include<mutex>
#include<condition_variable>
#include<memory>
#include<cstdio>



template<typename T>
class threadsafe_queue
{
private:
    struct node
    {
        std::shared_ptr<T> data;
        std:: unique_ptr<node> next;
    };

    std::mutex head_mutex;
    std::unique_ptr<node> head;
    std::mutex tail_mutex;
    node * tail;
    std::condition_variable data_cond;

private:
    node * get_tail()
    {
        std::lock_guard<std::mutex> tail_lock(tail_mutex);
        return tail;
    }

    std::unique_ptr<node> pop_head()
    {
        std::unique_ptr<node> old_head = std::move(head);
        head = std::move(old_head->next);
        return old_head;
    }

    std::unique_lock<std::mutex> wait_for_data()
    {
        std::unique_lock<std::mutex> head_lock(head_mutex);
        data_cond.wait(head_lock,[&]{return head.get() != get_tail();});
        return std::move(head_lock);
    }

    std::unique_ptr<node> wait_pop_head()
    {
        std::unique_lock<std::mutex> head_lock(wait_for_data());
        return pop_head();
    }

    std::unique_ptr<node> wait_pop_head(T & value)
    {
        std::unique_lock<std::mutex> head_lock(wait_for_data());
        value = std::move(*head->data);
        return pop_head();
    }

    std::unique_ptr<node> try_pop_head()
    {
        std::lock_guard<std::mutex> head_lock(head_mutex);
        if(head.get() == get_tail())
        {
            return std::unique_ptr<node>();       
        }
        return pop_head();
    }

    std::unique_ptr<node> try_pop_head(T & value)
    {
        std::lock_guard<std::mutex> head_Lock(head_mutex);
        if(head.get() == get_tail())
        {
            return std::unique_ptr<node>();
        }
        value = std::move(*head->data);
        return pop_head();
    }
public:
    threadsafe_queue():
        head(new node), tail(head.get())
    {

    }
    threadsafe_queue(const threadsafe_queue &) = delete;
    threadsafe_queue & operator=(const threadsafe_queue &) = delete;

    std::shared_ptr<T> try_pop()
    {
        std::unique_ptr<node> old_head = try_pop_head();
        return old_head ? old_head->data : std::shared_ptr<T>();
    }
    
    bool try_pop(T & value)
    {
        std::unique_ptr<node> const old_head = try_pop_head(value);
        return old_head != nullptr;
    }

    std::shared_ptr<T> wait_and_pop()
    {
        std::unique_ptr<node> const old_head = wait_pop_head();
        return old_head->data;
    }
    
    void wait_and_pop(T & value)
    {
        std::unique_ptr<node> const old_head = wait_pop_head(value);
    }

    void push(T new_value)
    {
        std::shared_ptr<T> new_data(std::make_shared<T>(std::move(new_value)));
        std::unique_ptr<node>p(new node);
        {
            std::lock_guard<std::mutex> tail_lock(tail_mutex);
            tail->data = new_data;
            node * const new_tail = p.get();
            tail->next = std::move(p);
            tail = new_tail;
        }
        data_cond.notify_one();
    }
    bool empty()
    {
        std::lock_guard<std::mutex> head_lock(head_mutex);
        return (head.get() == get_tail());
    }
};

template<typename MessageType>
class CMessager
{
private:
    threadsafe_queue<MessageType> mq;
    std::mutex timed_mtx;
    std::condition_variable timed_cv;
public:

    void Send(MessageType type)
    {
        mq.push(type);
        timed_cv.notify_one();
    }

    void Receive(MessageType & value, uint16_t timeOut = -1)
    {
        if(timeOut < 0)
        {
           mq.wait_and_pop(value);
        }
        else
        {
            std::unique_lock<std::mutex> lock(timed_mtx);
            timed_cv.wait_for(lock, std::chrono::milliseconds(timeOut), [&]{
                return !mq.empty();
            });
            mq.try_pop(value);
        }
    }
};

struct times
{
    int a;
    int b;
    times()
    {
        a = 0;
        b = 0;
    }
    times(int aa, int bb)
    {
        a = aa;
        b = bb;
    }
};


int main(int argc, char const *argv[])
{
    CMessager<times> mq;
    std::atomic_int cnt = 0;
    std::thread t1([&]{
        while(true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout <<"send\n";
            mq.Send(times(cnt++, cnt));
        }
    });

    std::thread t2([&]{
        while(true)
        {
            times value (-1, -1);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            mq.Receive(value, 100);
            printf("Receive %d, %d \n", value.a, value.b);
        }
    });

    std::thread t3([&]{
        while(true)
        {
            times value (-1, -1);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            mq.Receive(value, 100);
            printf("Receive3 %d, %d \n", value.a, value.b);
        }
    });

        std::thread t4([&]{
        while(true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout <<"send4 \n";
            mq.Send(times(cnt++, cnt));
        }
    });


    t2.join();
    t3.join();
    t1.join();
    return 0;
}
