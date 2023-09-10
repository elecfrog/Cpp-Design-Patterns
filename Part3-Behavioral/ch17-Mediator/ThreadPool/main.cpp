#include "ThreadPool.hpp"

int main() {
    ThreadPool pool{4};
    mutex mtx;
    for (int idx = 0; idx < 10; ++idx) {
        pool.AddTask([&, idx] {
            {
                lock_guard<mutex> lock(mtx);
                cout << "Task " << idx << " is running!" << endl;
            }
            this_thread::sleep_for(500ms);
            {
                lock_guard<mutex> lock(mtx);
                cout << "Task " << idx << " is done!" << endl;
            }
        });
    }

    return 0;
}