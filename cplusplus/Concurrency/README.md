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
2. 如何等待一个事件或其他条件,既当一个线程等待另外一个线程完成任务。有很多种情况可以完成，如方式（1）它可以持续检查共享数据标志（用于做保护工作的互斥量），直到另一个线程完成工作后对这个标记重设，这种方式很浪费处理器资源（线程不断消耗执行时间去持续检查标志，且上锁后其他线程就被阻挡在外面持续等待）。方式(2)使用在周期性间歇中，检查。
```c++
   bool flag;
   std::mutex m;

   void wait_for_flag()
   {
      std::unique_lock<std::mutex> lk(m);
      while(!flag)
      {
         lk.unlock();
         std::this_thread::sleep_for(std::chrono::milliseconds(100));
         lk.lock();
      }
   } //周期性休眠，检查flag是否结束。不需要一直去抢占CPU。但也很难确定正确的休眠时间。太短和太长和没有休眠一样，都浪费执行时间。太长休眠，会让任务等待线程醒来。
```
（3）如今在c++11标准中，推荐使用c++标准库提供的工具去等待事件的发生。通过另一线程触发等待事件的机制三最基本的唤醒方式，这种机制就是“条件变量”。一个条件变量会与多个事件或其他条件相关，并且一个或多个线程会等待条件的达成。当某些线程被终止时，为了唤醒等待线程，终止线程将会向等待着的线程广播“条件达成”的信息。

3. 使用c++ 11 14 17标准库实现等待条件达成，有std::condition_variable 和 std::condition_variable_any,均在头文件<condition_variable>中，两者都需要一个互斥量一起才能工作（互斥量三为了同步），前者仅限于与std::mutex一起工作,后者可以和任何满足最低标准的互斥量一起工作.
由于std::condition_variable_any更为通用所以就会产生额外的开销。故使用std::condition_variable作为首选。对灵活性有硬性要求才会去考虑std::condition_variable_any.
```c++
    std::mutex mut;
    std::queue<data_thunk> data_queue;
    std::condition_variable data_cond;

    void data_preparation_thread()
    {
        while(more_data_to_prepare())
        {
            data_chunk const data = prepare_data();
            std::lock_guard(std::mutex) lk(mut);
            data_queue.push(data);
            data_cond.notify_one();
        }
    }

    void data_processing_thread()
    {
      while(true)
      {
         std::unique_lock<std::mutex> lk(mut);
         data_cond.wait(
            lk,[]{return !data_queue.empty();}
         );
         /*
            lambda表达式做wait的谓词，wait会去检查谓词，如果为true返回，反之如果为false，wait会去解除互斥量，并将这个线程阻塞/等待，直到有其他线程调用notify_one通知条件变量，则该线程获取将被唤醒，然后再持有互斥锁，并再次检查条件是否满足。
            wait是谓词条件满足则返回并持有互斥锁，不满足则解锁使线程等待。
            lock_guard没有这么灵活，锁住就是一直锁，直到解锁。
         */
         
         data_chunk data = data_queue.front();
         data_queue.pop();
         lk.unlock();
         process(data);
         if(is_last_chunk(data))
            break;
      }
    }
```
   std::condition_variable::wait是对“忙碌-等待”的一种优化，不理想的方式三使用简单的循环来实现。
```c++
   void wait(std::unique_lock<std::mutex> &lk, Predicate pred)
   {
      while(!pred())
      {
         lk.unlock();
         lk.lock();
      }
   }
```
4. 使用队列在多线程中进行转移数据是很好的选择。做得好的话，同步操作可以限制在队列内部，同步问题和条件竞争出现的概率也会降低。消息队列就是很常见的也是一种线程安全的队列，如boost库中的message_queue 。
也可以自己实现一个线程安全的队列。,什么时候使用notify_all？ 可以在线程准备数据时，就用, notify_all 让所有wait的线程去检查他们的条件是否满足。

5. 使用std::condition_variable让线程等待只能等待一次，当条件为true就不会再等待条件变量了，故一个条件变量可能并非同步机制的最好选择。尤其是，条件在等待一组可用的数据块时。在这种情况下可以使用期望值 future。

6. 使用期望值等待一次性事件。当线程需要等待特定的一次性事件时，某种程度上来说需要知道这个事件在未来的期望结果。之后，这个线程会周期性（较短的周期）的等待或检查，事件是否触发；检查期间也会执行其他任务。此外，等待任务任务期间它可以先执行另外一些任务，直到对应的任务触发，而后等待期望值的状态就会变为就绪。一个期望值可能三数据相关的，也可能不是。当事件发生时（并且期望状态为就绪），并且这个期望值不能被重置。
c++标准库中有两种期望值，在<future>文件中，唯一期望值和共享期望值。仿照了std::unique_ptr和std::shared_ptr。std::futrued的实例只能与一个指定事件相关联。而std::shared_future的实例能关联多个事件，该多个事件都同时变为就绪状态，且可以访问与事件相关的任何数据。数据关联可以使用std::unique_ptr和std::shared_ptr的模板参数。与数据无关，可以使用std::future和std::shared_future。期望值本身不提供同步访问。当多个线程需要访问一个独立期望值时，必须使用互斥量进行保护。

使用场景

* 一个需要长时间计算出的值，又不迫切需要这个值。
```c++
   //
   #include<future>
   #include<iostream>

   int find_the_answer_to_ltuae();
   void do_other_stuff();

   int main()
   {
      std::future<int> the_answer = std::async(fint_the_answer_to_ltuae);//启动一个异步任务。
      do_other_stuff();//做其他事
      std::cout << "answer = " <<the_answer.get();//需要获取这个值，会阻塞线程直到期望状态为就绪。
   }

```
* std::async可以传递参数。
```c++
   #include<string>
   #include<future>
   struct X
   {
      void foo(int ,std::string const&);
      std::string bar(std::string const &);
   };

   X x;
   auto f1 = std::async(&X::foo, &x, 42, "hello");//调用 P->foo(42, "hello") p 为指向x的指针
   auto f2 = std::async(&X::bar, x, "goodbye");//调用 tempx.bar("goodbye") tempx为x的拷贝副本


   struct Y
   {
      double operator()(double);

   };

   Y y;
   auto f3 = std::async(Y(), 3.141);//调用tempy(3.141), tempy 通过Y的移动构造函数得到
   auto f4 = std::async(std::ref(y)，2.718)；//调用y(2.718)
   

   X baz(X&);
   std::async(baz, std::ref(x)); //调用baz(x)

   class move_only
   {
   public:
      move_only();
      move_only(move_only &);
      move_only(move_only const &) = delete;
      move_only & operator(move_only &);
      move_only & operator(move_only const &) = delete;

      void operator();
   };

   auto f5=std::async(move_only());//调用temp(), temp是通过std::move(move_only)得到。

```

*  可以额外传递一个参数给std::async，std::launch::defered(函数调用延迟到wait或者get函数调用才执行) 和 std::launch::async （表明函数必须在其所在的独立线程上执行，该方式也三默认的）,或二者选一std::launch::sync | std::launch::defered。
```c++
   auto f6 = std::async(std::launch::async, Y(), 1, 2); //在新线程执行
```

7. 任务与期望值关联

std::packaged_task<>对一个函数或者可调用对象，绑定一个期望值。当调用 std::packaged_task<>对象时，它就会调用相关函数或可调用对象，将期望值状态设置为就绪，返回值也会被存储。可用于构建线程池的结构单元或用于其他任务的管理。如：在任务所在线程上运行其他任务，或将它们顺序的运行在一个特殊的后台线程上。

```c++
   template<>
   class packaged_task<std::string(std::vector<char>*, int)>
   {
      public:
         template<typename Callable>
         explicit packaged_task(Callable && f);
         std::future<std::string> get_future();
         void operator()(std::vector<char>*, int);
   };

```

8. std::promises

9. 多线程的等待，std::future只能使得一个等待线程可以同步数据，而其他线程的数据三不同步的。由于std::future独享同步结果的所有权，只能get一次性的数据。std::shared_future可以让多个线程等待同一个事件。std::future是只能移动的，而std::shared_future的实例三可以拷贝的,固多个对象可以引用同一关联期望值的结果。每个std::shared_future的独立对象上，成员函数调用返回的结果还是不同步的，固多个线程访问一个独立对象时避免数据竞争还是要使用锁来进行访问保护。
* 可以让每个线程都拥有自己对应的拷贝对象，拥有自己的std::shared_future对象去获取结果，这样多个线程访问共享同步结果就是安全的。
* std::shared_future的实例同步std::future实例的状态。当std::future对象没有与其他对象共享同步状态所有权，那么所有权必须使用std::move将所有权传递到Std::shared_future。
```c++
   std::promise<int>p;
   std::future<int>f(p.get_future());
   assert(f.vaild());//期望值合法
   std::shared_future<int> sf(std::move(f));//f所有权给sf
   assert(!f.valid());//期望值不合法
   assert(sf.vaild());//合法
```

10. 限定等待的时间

有两种指定超时的方式：一时“时延”如（30ms）,二是“绝对时间点”（北京时间 xxxx.xx.xx.xx.xx.xx）.
处理等待函数提供变量，处理时延的变量也_for为后缀，处理绝对时间的变量以_until为后缀.
则std:condition_variable两个成员函数wait_for 和 wait_until.

* c++标准库 时钟。时钟是一个类，提供四种信息。当前时间、时间类型、时钟节拍、通过时钟节拍的分布，判断时钟是否稳定。
* std::chrono::system_clock::now()返回系统时钟的当前时间。
* 特定时间可以通过some_clock::time_point的数据来指定。
* 时钟节拍为1/x(x在不同硬件上有不同的值)秒，这是由时钟周期决定，当一个时钟1秒有25个节拍，因此一个周期为std::ratio<1,25>.当一个时钟的时钟节拍每2.5秒一次，周期可以表示为 std::ratio<5,2>.
* 通常情况下 std::chrono::system_clock是不稳定的,通过is_steady判断这个时钟是否稳定。
* c++标准库提供了一个稳定时钟 std::chrono::steady_clock.
* 可将时间点转为time_t类型
* std::chrono::high_resolution_clock 为标准库中具有最小节拍周期的时钟。
* 时延，标准库提供std::chrono::duration<>,如std::chrono::duration<short, std::ratio<60, 1>> 表示60秒为1分钟存放在short中。 当需要毫秒级计数存在double类型中时，可写成std::chrono::duration<double,std::ratio<1,1000>> 表示 1s等于1000ms
* std::chrono中有 nansoseconds(纳秒)、microseconds（毫秒）、seconds（秒）、minutes（分）和hours（小时）。
* 时转化
  ```c++
   std::chrono::milliseconds ms(54802);
   std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(ms);//54s
  ```
* 基于时延的等待可由std::chrono::duration<>来完成,wait_for等待完成后会有个状态值，std::future_status::ready/timeout/deferred.基于时延的等待三使用内部库中的稳定时钟来计时的。不论系统时钟被调整，这都将耗时35ms
```c++
   std::future<int> f = std::async(some_task);
   if(f.wait_for(std::chrono::milliseconds(35)) == std::future_status::ready)
      do_something_with(f.get());
```

* 时间点，用std::chrono::time_point<>类型模板来表示，有两个参数，第一个参数为指定所需要使用的时钟、第二个参数为表示时间的计量单位（std::chrono::duration）,一个时间点的值就是时间的长度。
```c++
   std::chrono::time_point<std::chrono::system_lock, std::chrono::minutes>

   //通过time_point 可以实现时延duration 的+ - 
   std::chrono::hight_resolution_clock::now() + std::chrono::naoseconds(500)
```

* 等待一个条件变量，具有超时功能
   ```c++
   std::conditon_variable cv;
   bool done;
   std::mutex mtx;
   bool wait_loop()
   {
      auto const timeout = std::chrono::steady_clock::now() + std::chrono::millseconds(500);
      std::unique_lock<std::mutex> lk(m);
      while(!done)
      {
         if(cv.wiat_until(lk, timeout) == std::cv::status::timeout)
          break;
      }
      return done;
   }
   ```

11. 使用消息传递的同步操作

当没有共享数据时，每个线程可以进行独立思考，其行为纯粹是基于所接收到的信息。尽可能降低多个线程共享数据。为了线程之间的通信，消息队列必须三共享的，具体的细节要包含在库中。
```c++
   struct card_inserted
   {
      std::string account;
   };

   class atm
   {
      messaging::receiver incoming;
      messaging::sender bank;
      messaging::sender interface_hardware;
      void (atm:: *state)();//声明一个函数指针

      std::string account;
      std::string pin;

      void waiting_for_card()
      {
         interface_hardware.send(display_enter_card());//发送消息到界面进行等待
         incoming.wait().//等待传入消息进行处理
         handle<car_inserted>(
            [&](card_inserted const &msg)
            {
               account = msg.account;
               pin="";
               interface_hardware.send(display_enter_pin());
               state = &atm::getting_pin;//切换到getting_pin状态
            }
         )
      };
   }

   void getting_pin()
   {
      incoming.wait()
         .handle<digit_pressed>(
            [&](digit_pressed const & msg)
            {
               unsigned const pin_length = 4;
               pin += msg.digit;
               if(pin.length() == pin_length)
               {
                  bank.send(verify)pin(account, pin, incoming);
                  state=&atm::verifying_pin;
               }
            }
         )
         .handle<clear_last_pressed>(
            [&](clear_last_pressed const & msg)
            {
               if(!pin.empty())
               {
                  pin.resize(pin.length() - 1);
               }
            }
         )
         .handle<cancel_pressed>(
            [&](cancel_pressed const & msg)
            {
               state = &atm::done_precessing;
            }
         )
   }

   public:
      void run()
      {
         state = &atm::waiting_for_card;//函数指针指向waiting_for_card函数
         try
         {
            for(;;)
            {
               (this->*state()); //不断运行。
            }
         }
         catch(messaging::close_queue const &)
         {

         }
      }
```
参与者模式(Actor model):某个模块有运行在独立线程上的终端接口。

12. 等待多个期望值

应用场景：有很多数据需要处理，并且每个数据都可以单独处理，则可以使用异步的方式进行，产生异步任务来处理数据项，每个任务通过期望值返回处理过后的数据，需等待所有任务完成时，才能获取最终结果。

```c++
   std::future<FinalResult> process_data(std::vector<MyData> & vec)
   {
      size_t const chunk_size = whatever;
      std::vector<std::future<chunkResult>> results;
      for(auto begin = vec.begin(), end= vec.end(); beg != end;) {
         size_t const remaining_size = end -begin;
         size_t const this_chunk_size = std::min(remaining_size, chunk_size);
         results.push_back(std::async(process_chunk, begin, begin + this_chunk_Size));
         begin += this_chunk_size;
      }
      return std::async([all_results = std::move(results)](){
         std::vector<ChunkResult> v;
         v.reserve(all_results.size());
         for(auto & f :all_results)
         {
            v.push_back(f.get());
         }
         return gther_results(v);
      });
   }
```
上述方式存在问题，会在 f.get处反复唤醒和休眠，不仅占用了线程资源，且对之后的期望值的操作会增上下文切换频率从而增加了很多额外的开销。

使用 std::experimental::when_all可以避免这种等待和切换问题，将一组需要等待的期望值传入when_all函数中，会返回一个新的期望值，当传入的所有期望值的状态都为就绪时，这个新的期望值就位为就绪，这样这个期望值可以和持续性配合起来一起处理其他任务。
```c++
   std::experimental::future<FinalResult> process_data(
      std::vector<MyData> &vec)
   {
      size_t const chunk_size = whatever;
      std::vector<std::experimental::future<ChunkResult>> results;
      for(auto begin = vec.begin()， end = vec.end(); beg != end) {
         size_t const remaining_size = end -begin;
         size_t const this_chunk_size = std::min(remaining_size, chunk_size);
         results.push_back(
            spawn_async(
               process_chunk, begin, begin + this+chunk_size
            )
         );
         begin += this_chunk_size;
      }
      return std::experimental::when_all(
         results.begin(), results.end()
      ).then(
         [](std::future<std::vector<experimental::future<ChunkResult>>> ready_results){
            std::vector<std::experimental::future<ChunkResult>> all_results =
            ready_results.get();
            std::vector<ChunkResult> v;
            v.reserve(all_results.size());
            for(auto & f : all_results) {
               v.push_back(f.get());
            }
            return gather_results(v);
         }
      )
   }
```

也有一种std::experimental::when_any ，当期望值组中任意一个期望为就绪态，那么这个新期望值的状态就为就绪。

应用场景：当有一大堆数据里找一个符合要求的值，这里的数据集中有很多符合要求的，随便一个都可以。这种任务可以并行的。每个任务去检查数据的子集，如果有线程找到了合适的值，这个线程就会设置有一个标志，让其他线程停止搜索，并返回结果。这种情况，即使其他任务还没有完成清理，还是希望第一个完成搜索任务的线程对数据进一步处理。
```c++
   std::experimental::future<FinalResult> find_and_process_value(std::vector<MyData> &data)
   {
      unsigned const concurrency = std::thread::hardware_concurrency();
      unsigned const num_tasks = (concurrency > 0) ? concurrency : 2;
      std::vector<std::experimental::future<MyData *>> results;
      auto const chunk_size = (data.size() +num_tasks - 1) / num_tasks;
      auto chunk_begin = data.begin();
      std::shared_ptr<std::atomic<bool>> done_flag = std::make_shared<std::atmoic(bool)>>(false);
      for(unsigned i = 0; i <num_tasks; i++>) {
         auto chunk_end = (i < (num_tasks - 1) ? chunk_begin + chunk_size : data.end());
         results.push_back(spawn_async([=]{
            for(auto entry = chunk_begin; ! *done_flag && (entry != chunk_end); ++entry){
               if(matches_find_criteria(*entry)) {
                  *done_flag = true;
                  return & *entry;
               }
            }
            return (MyData *) nullptr;
         }));
         chunk_begin = chunk_end;
      }
      std::shared_ptr<std::experimental::promise<FinalResult>> final_result = std::make_shared<std::experimental::promise<FinalResult>>();
      struct DoneChek {

      }
   }
```

13. 简单的栅栏机制 std::experimental::barrier

简单版::barrier

灵活版本:flex_barrier

应用场景：有一组线程对某些数据进行独立的任务，故不需要进行同步操作。但当所有线程都必须处理下个数据前都必须完成当前任务。这就需要栅栏机制了。通过栅栏机制，当一组线程中的最后一个线程抵达时，所有线程才会被释放，才能继续接下来的任务。

```c++
   result_chunk process(data_chunk);
   std::vector<data_chunk> divide_into_chunks(data_block data, unsigned num_threads);

   void process_data(data_source & source, data_sink &sink) {
      unsigned const concurrency = std::thread::hardware_concurrency();
      unsigned const num_threads = (concurrency > 0) ? concurrency :2;

      std::experimental::barrier sync(num_threads);
      std::vector<joining_thread> threads(num_threads);

      std::vector<data_chunk> chunks;
      result_bolock result;

      for(unsigned i = 0; i <num_threads; i++) {
         threads[i] = joining_thread([&,i]{
            while(!source.done()){
               data_block current_block = 
               source.get_next_data_block();
               chunks = divide_inito_chunks(current_block, num_threads);
            }
            sync.arrive_and_wait();
            result.set_chunk(i, num_threads, process(chunks[i]));
            sync.arrive_and_wait();
            if(!i) {
               sink.write_data(std::move(result));
            }
         });
      }
   }
```


## c++内存模型与原子类型操作

1. c++内存四条原则：
* 每个变量都是一个对象，包括作为其成员变量的对象。
* 每个对象至少占有一个内存位置
* 基本类型都有确定的内存位置（无论类型大小）
* 相邻位域是相同内存中的一部分
  

2. 原子操作：是一个不可分割的操作。
3. c++ 标准库中提供了标准原子类型，(atomic)头文件中，里面的类型都是原子的，每个类型基本都有一个is_clock_free()成员函数，可以查询某原子类型的操作三原子指令还是内部使用锁实现。
4. atomic_基本类型（原子类型）、特化类为std::atomic<基本类型>
5. std::atomic<>类模板也可以使用用户自定义类型创建对应的原子变量。
   ```c++
      //使用std::atomic_flag 实现自旋互斥锁
      class spinlock_mutex
      {
         std::atomic_flag flag;
      public:
         spinklock_mute();
         flag(ATOMIC_FLAG_INIT){}

         void lock()
         {
            while(flag.test_and_set(std::memeroy_order_acquire));
         }

         void unlock()
         {
            flag.clear(std::memeory_order_release);
         }
      }
   ```