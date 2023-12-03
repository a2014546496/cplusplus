// #include <boost/interprocess/ipc/message_queue.hpp>
// #include <iostream>
// #include <vector>
// #include<thread>

// using namespace boost::interprocess;

// void send_fun()
// {
//     try
//     {
//         /* code */
//         message_queue::remove("message_queue");

//         message_queue mq(create_only, "message_queue", 100, sizeof(int));

//         for (int i = 0; i < 100; i++)
//         {
//             mq.send(&i, sizeof(i), 0);
//         }
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << '\n';
//     }
// }



// int main(int argc, char const *argv[])
// {
//     std::thread t2(send_fun);
//     std::thread t1(recev_fun);
//     t1.detach();
//     t2.detach();
//     while(1)
//     {
//         sleep(30);
//         std::cout <<"run_____";
//     }
//     return 0;
// }

#include <boost/interprocess/ipc/message_queue.hpp>
#include <iostream>
#include <string>
#include <thread>

struct temp
{
    int a;
    int b;
};

int main() {
    //创建一个消息队列
    boost::interprocess::message_queue::remove("message_queue1");
    boost::interprocess::message_queue mq(boost::interprocess::open_or_create, "message_queue1", 100, sizeof(temp));

    std::thread t1([&](){
        // 在一个线程中发送消息
        temp data_to_send = {40,20};
        std::cout <<"send\n";
        mq.send(&data_to_send, sizeof(temp), 0);
        std::cout <<"sended\n";
    });

    std::thread t2([&](){
    // 在另一个线程中接收消息
    temp received_data;
    size_t recv_size;
    unsigned int priority;
    std::cout <<"receive\n";
    mq.receive(&received_data, sizeof(received_data), recv_size, priority);

    // 打印接收到的消息
    std::cout << "Received data: " << received_data.a <<" "<< received_data.b << std::endl;
    });


    t1.detach();
    t2.detach();
    // 关闭消息队列
    while(1){sleep(1); std::cout <<"ok\n";}
    boost::interprocess::message_queue::remove("message_queue1");

    return 0;
}
