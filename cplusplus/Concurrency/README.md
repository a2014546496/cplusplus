# c++ 并发编程
## 并发与并行
1. 区别
* 并发：多个任务交互占用cpu资源的进行作业，在单核cpu上表现为轮流完成一个任务的一部分。在多核cpu表现为同一时间点同时执行多个任务。是一种不严格（假）并行。由于cpu运算速度极快，给用户一种在同一时间点执行了多个任务的错觉。
* 并行：可理解为必须在同一时间点上同时执行多个任务的并发，也就表明必须在一个多核cpu或者多颗cpu才能够实现这种特性。
2. 为什么使用并发？
* 主要关注分离和性能，结合其一种或二者都有的特点。
* 分离点：及在编写软件时，将相关代码与无关代码分离，使得程序更容易理解和测试，减少出错的可能性。
* 性能点：提高性能。（1）将一个单个任务分成几部分的子任务，各自并行运行，从而降低总运行时间，这就是任务并行。由于各个子任务之间可能存在依赖，导致实现过程复杂。有两种情况，一种情况三一个线程执行算法的一部分、另外一个现场执行算法的另外一部分。另外一种情况，每个线程在不同的数据部分上执行相同的操作，这就是一个易并行。
3. 使用并发需要注意的情况
*  使用并发的代码，难以理解也容易引发更多错误。只有在足够清楚性能提高很大或者分离点清晰，才使用并发。
*  线程所使用的资源三有限的，过多的线程会导致消耗过多的操作系统资源，使得操作系统整体上运行更加缓慢。
4. 并发中过多的线程可能出现的情况
* 处于C/S模式的服务器中为每一个连接启动一个独立的线程，对于少量的连接可以正常工作。当需要大量连接时，也会由于过多线程导致耗尽系统资源。这种情况可以使用线程池化技术。
* 越多的线程，操作系统就需要越多的上下文切换，增加占用正常工作的时间成本。

## c++中的线程
1. 使用c++11标准，能够编写不依赖与平台的多线程代码。
2. 熟悉c++11标准的 thread库  
std::thread对象:  
```c++
 void doSomeThing()
 {
    .....
 }
 std::thread myThread(doSomeThing); //创建了一个线程,该线程构造完成后直接执行doSomeThing函数
``` 
3. thread  的两个重要函数，join，detach。当线程创建后，调用join函数，则会阻塞其调用线程，完成当前线程（被调用的线程）的任务后再继续执行调用线程。thread以detach的方式运行，则与调用线程分离，调用线程与当前线程竞争cpu资源，若调用线程先结束，则被调用线程会异常。一个线程只能调用join或detach一次，二者不能同时被一个线程调用。

常见用法example:
```c++
   //one 使用RAII方式，线程为类的成员变量
   class threadTest
   {
      std::thread &t;
   public:
      explicit threadTest*sd::thread & t_):t(t_){}

      threadTest(threadTest const &) =delete;
      threadTest &operator = (threadTest const &) =delete;

      ~threadTest()
      {
         if(t.joinable()) //若线程处于可运行状态
         {
            t.join(); // 在析构结束前阻塞，等待线程执行完毕。
         }
      }
   }


   class thestTestTwo
   {
      std::thread &t;
   public:
      void fun()
      {
         t = thread([](){...}); 
         t.detach(); //创建一个线程，并以dettach方式运行。
      }
   }

```
重点注意线程以detach方式运行。调用了detach方式后，线程在后台运行，分离后的线程不能被加入，c++运行库确保，线程退出时，相关资源能正确回收，后台线程的归属和控制c++的运行库都会处理。这种方式一般称为守护线程，特点是长时间运行，生命周期可能从一个应用开始到结束，一般在后台监视文件系统，或则对缓存进行清理，或对数据结构优化。

4. 对线程函数传入参数：
```c++

   //普通参数传入的方式
   void f(int i , std::string const & s);
   ...
   std::thread t(f, 3, "hello");

   //对字符数组指针参数传入
   void test(int some_param)
   {
      char buffer[1024];
      sprintf(buffer, "%d", some_param);
      std::thread t(f,3,std::string(buffer)); // 传入前显示转化为string可以避免莫名的崩溃现象。
   }

   //传入引用参数
   void updateData(classOne &data);
   void test(classOne param)
   {
      /*std::thread t(updateData, param); 
         这种方式 线程的构造函数并不知晓param给线程函数三引用的方式，所以会拷贝一份传给线程函数.
      */

     //使用 std::ref显示的告诉线程构造函数该参数为引用形式，这样传给线程函数的就不是拷贝了的参数。
     sttd::thread t(updateData, std::ref(param));
   }
```
5. 转移线程所有权, 使用 std::move()

6. 标识线程，线程标识类型为 std::thread::id,通过线程的成员函数get_id获取，或者当前线程调用std::this_thread::get_id()获取.
```c++
   std::thread::id master_thread;
   void some_core_part_of_algorithm()
   {
      if(std::this_thread::get_id() == master_thread)
      {
         do_master_thread_work();
      }
      do_common_work();
   } 
```

## 多线程之间共享数据

1. 条件竞争：多个线程对数据共享进行读写操作。
2. 使用互斥量进行保护共享数据 ,在 c++中使用头文件为mutex里的一个类为std::mutex
```c++
   #include<list>
   #include<mutex>
   #include<algorithm>
   
   std::list<int> some_list;
   std::mutex some_mutex;

   void add_to_list(int new_value)
   {
      std::lock_guard<std::mutex> guard(some_mutex); //声明及上锁
      some_list.push_back(new_value);
   }//出作用域，析构解锁

   bool list_contains(int value_to_find)
   {
      std::lock_guard<std::mutex> guard(some_mutex);
      return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
   }

```

3. lock_guard、unique_guard的区别，从代码层面上,unique_guard比lock_guard灵活，可根据需要unlock同时具备lock_guard的特点。从原理上讲unique_guard支持粒度小的互斥.

4. 如何保护不常更新的数据结构,c++ 14 17 可以使用 std::shared_mutex 以及std::shared_timed_mutex与lock_gurad 和 unique_lock配合使用。 ，std::shared_mutex的性能更高，但都依赖于处理器数量。这两种锁统称为读者-写者锁，及支持仅一个写线程独占资源或多个读线程共享资源，而不像std::mutex不论读写线程都上锁然后解锁影响性能。

```c++
   #include<map>
   #include<string>
   #include<mutex>
   #include<shard_mutex>

   class dns_entry;

   class dns_cache
   {
      std::map<std::string, dns_entry> entries;
      mutable std::shared_mutex entry_mutex;
   public:
      dns_entry find_entry(std::string const & domain) const
      {
         /*
            提供共享锁（读者锁）
        */
         std::shared_lock<std::shard_mutex> lk(entry_mutex); 
         /*  shard_mutex 与 mutex
            区别：当任一个线程拥有一个共享锁时，这个线程或尝试获取一个独占锁，一直到其他线程放弃锁时；当任一线程有一个独占锁时，这个线程就会去获取一个独占锁时，其他线程就无法获取共享锁和独占锁，直到第一个线程放弃拥有的锁。
         */
     
         std::map<std::string, dns_entry>::const_iterator const it = entries.find(domain);
         return (it == entries.end()) ? dns_entry():it->second;
      }

      void update_or_add_entry(std::string const & domain, dns_entry const &dns_details)
      {
         /*
            提供独占锁(写者锁)
         */
         std::lock_guard<std::shared_mutex> lk(entry_mutex);
         entries[domain] = dns_details;
      }
   }
```

5. 嵌套锁，std::mutex不支持嵌套锁，若要嵌套可以使用std::recursive_mutex类，与std::mutex的区别仅在于同一个线程的单个实例std::recursive_mutex对象可以获取多个锁。上几次锁就必须释放几次。


## 同步并发操作

1. 同步（不仅需要对数据保存，还需要控制多个线程之间的执行顺序），如一个线程完成前，需要等待另外一个线程执行完成。条件变量可以解决这些问题，c++标准库提供了条件变量工具。condition variables 和期望值futures。
2. 
