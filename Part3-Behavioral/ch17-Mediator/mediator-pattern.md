# Mediator Pattern

components may go in and out of a system at any time

- Chat Room
- Players in Genshin Impact
- [UE `UWorld` Class](https://docs.unrealengine.com/5.2/en-US/API/Runtime/Engine/Engine/UWorld/)

Issues:
Those references may go dead

Solution:
**have then all refer to some cent ral component that facilitates communication**

### Chat Room

In the example of Chat Room, objects communicate with each other by ChatRoom object, which is the mediator in this
situation.

```cpp
struct ChatRoom;
struct Person { ChatRoom *room{nullptr}; };
```

one person object may has many chat functions, speaking, personal messages, receiving...

But one person holds a `ChatRoom` pointer, person itself never modify this pointer unless initialized it.

Its change happens in

```cpp
void ChatRoom::join(Person *p) {
    string join_msg = p->name + " joins the chat";
    broadcast("room", join_msg);
    p->room = this;
    people.push_back(p);
}
```

while the person was added into the chat room.

In the case, person the instance may go in or quit, but ChatRoom is the mediator to hold and act as a channel to
communicate.

### Event Broker and Messages
Mediator could be a communication service center, it could support:
- Broadcast: it receives messages from one instance and broadcast other instances registered
- Multicast: it could cast messages to a group of objects by filtering them
- Single Point: it also could transmit messages from one instance to another instance

This example also implemented by using Qt signals-slots, it sends a message from player to coach by an intermediate object,
`Game`. It could also be seen as a global object. It was similar to the UWorld class in the unreal Engine.

## Producer-Consumer Model => Thread Pool In Practice
### Intro
是中介者模式的一种体现
有容器型和平台型两种
容器型本质：增加存放数据的容器
    信  => 邮递员 => 分发信
    信  => 邮筒 => 邮递员 => 分发信
    信  => 邮筒 => 邮递员 => 自取柜 => 分发信
    ...MORE COMPLEX CHAIN...
平台型本质：附加接口，方便两方
    Amazon => A platform provide a container for both producers and consumers
    Amazon Services 
        => Ranking, Commenting, Filtering, Advertisement...
        => Attached Music, Video and other platform and services...


Producer => Tasks
Consumers => Thread Pool

Future and Promises are used to transfer data between threads. In C++, they are `std::future` and `std::promise`. one std::future object and an std::promise object set up a "shared state" between threads. they are thread-safe without explicit locking. It oftern refers to a **Producer-Consumer Model**.

### 
线程在 构造函数中就会触发创建，即就会运行，因此为了延迟其运行，我们可以用std::unique_ptr进行包裹
```cpp
unique_ptr<thread> pthread = nullptr;
```

### Why using thread pool?
Creating resources and Destory resources take time.
We can pre-define a queue of resources.


### What is the thread pool
**Thread Pool**
1. 一个池子拥有固定数量的线程
2. 执行完任务后不停止
3. 共享任务队列，自行执行

线程创建：训练一个苦工
线程工作：让苦工去挖金子
线程析构：杀掉苦工

工作线程管理
1. CTOR 创建线程
2. DTOR 停止线程

任务队列
1. 存放任务的**容器**
2. 但是对于用CPU的任务来说
3. 公平
4. 队列这样的线性容器

_FIFO，但是带有优先级_
IO的任务比CPU的任务优先级高

链表式环形缓冲
不丢数据
反复利用内存  尽量少申请
不需要申请大内存 多少少量申请
需要手写

线程数组
任务队列

生产者向任务队列加任务
线程数组从任务队列取出任务

### Producer-Consumer Model
In this model, a **producer** thread will generate a result, and a **consumer** thread waits for the result. Here is a basic example to implement in C++ using `std::future` and `std::promise`.
```cpp
void produce(std::promise<int>& px) {  
    using namespace std::literals;
    int x = 42;   // result we need
    std::this_thread::sleep_for(2s);    
    // Store the result in the shared state  
    std::cout << "Promise sets shared state to " << x << '\n';  
    px.set_value(x);  
}  
  
void consume(std::future<int>& fx)  {  
    // Get the result from the shared state  
    std::cout << "Future calling get()...\n";  
    int x = fx.get();  
    std::cout << "Future returns from calling get()\n";  
    std::cout << "The answer is " << x << '\n';  
}  
  
int main() {  
    // setup promise and future objects  
    std::promise<int> prom;    
    std::future<int> fut = prom.get_future();    
    // threads  
    std::jthread thr_producer(produce, std::ref(prom));  
    std::jthread thr_consumer(consume, std::ref(fut));  
}
```
And expections should be hanled in `try-catch` blocks.

### Shared_Future
And if we direcly use is code for multiple futhre objects to read like this

```cpp
std::promise<int> prom;    
std::future<int> fut = prom.get_future();    
std::future<int> fut1 = prom.get_future();    
std::jthread thr_producer(produce, std::ref(prom));  
std::jthread thr_consumer(consume, std::ref(fut));  
std::jthread thr_consumer1(consume, std::ref(fut1));  
```
It is unsafe and UB. We need to solve it, so we use `std::shared_future`, as follows:
```cpp
std::promise<int> prom;    
std::shard_future<int> fut = prom.get_future();    
std::shard_future<int> fut1 = prom.get_future();   
std::jthread thr_producer(produce, std::ref(prom));  
std::jthread thr_consumer(consume, std::ref(fut));  
std::jthread thr_consumer1(consume, std::ref(fut1));  
```

