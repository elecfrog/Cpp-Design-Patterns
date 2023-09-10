/*
 * description:
 * author@elecfrog
 */
#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

using ThreadPoolTask = std::function<void()>;

struct ThreadPool {

    explicit ThreadPool(int numThreads)
            : stop(false) {
        for (int idx = 0; idx < numThreads; ++idx) {
            // add new thread into threads array
            threads.emplace_back([&] {
                for (;;) {
                    // using a unique_lock to control the lifetime manually
                    unique_lock<mutex> lock(mtx);

                    // using a conditional variable to 
                    // check if thread has a task
                    condition.wait(lock, [&] {
                        return !tasks.empty() || stop;
                    });

                    // if the flag is stop, and no tasks should be done, return it!
                    if (stop && tasks.empty()) return;

                    // fetch the front task from the task queue
                    ThreadPoolTask task(std::move(tasks.front()));
                    tasks.pop();
                    lock.unlock();
                    task();
                }
            });
        }
    }


    ~ThreadPool() {
        {
            lock_guard<mutex> lock(mtx);
            stop = true;
        }

        condition.notify_all();
        for (auto &&t: threads) {
            t.join();
        }

    }

    template<class Func, class ... Args>
    void AddTask(Func &&func, Args &&... args) {
        ThreadPoolTask task = bind(forward<Func>(func), forward<Args>(args)...);

//        ThreadPoolTask task = bind(forward<Func>(func), forward<Args>((args)...));

        {
            lock_guard<mutex> lock(mtx);
            tasks.push(move(task));
        }
        condition.notify_one();
        
    }

    // Threads Arrays
    vector<thread> threads;
    // Tasks Queue
    queue<ThreadPoolTask> tasks;
    mutex mtx;
    condition_variable condition;
    bool stop;
};