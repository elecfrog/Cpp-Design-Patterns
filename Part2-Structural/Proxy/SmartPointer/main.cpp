#include <memory>
#include <iostream>
#include <functional>
#include "UniquePointer/UniquePtr.hpp"
#include "UniquePointer/UniqueDeletePtr.hpp"
#include "UniquePointer/UniqueTuplePtr.hpp"

using namespace std;

void funcDeleter(int *p) { delete p; }

auto statelessLambdaDeleter = [](int *p) { delete p; };
std::function<void(int *)> foo = [](int *p) { delete p; };

int main() {


    int x = 2;
    auto statefulLambdaDeleter = [&, x](int *p) {
        delete p;
        cout << x << "XX" << endl;
    };

    elf::UniquePtr<int> uptr{new int(0)};
    uptr.release();

    unique_ptr<int, decltype(statelessLambdaDeleter)> udptrlambda(new int, statelessLambdaDeleter);
    unique_ptr<int, decltype(&funcDeleter)> udptrFunc(new int, &funcDeleter);

    elf::UniqueDeletePtr<int, decltype(statelessLambdaDeleter)> udptr0{new int, statelessLambdaDeleter};
    elf::UniqueDeletePtr<int, decltype(&funcDeleter)> udptr1{new int, funcDeleter};


    elf::UniqueTuplePtr<int, decltype(statelessLambdaDeleter)> utptr0{new int, statelessLambdaDeleter};
    elf::UniqueTuplePtr<int, decltype(&funcDeleter)> utptr1{new int, funcDeleter};

    string a;

    cout << "sizeof(foo) is " << sizeof(foo) << endl /* 8 byte with no any question! */
         << "sizeof(uptr) is " << sizeof(uptr) << endl /* 8 byte with no any question! */
         << "sizeof(statelessLambdaDeleter) is " << sizeof(statelessLambdaDeleter) << endl /* 1 byte*/
         << "sizeof(statefulLambdaDeleter) is " << sizeof(statefulLambdaDeleter) << endl /* 4 byte*/
         << "sizeof(&funcDeleter) is " << sizeof(&funcDeleter) << endl /* 8 byte with no any question! */
         << "sizeof(udptrlambda) is " << sizeof(udptrlambda) << endl  /* stateless => 8 byte, stateful => 16 bytes wired!*/
         << "sizeof(udptrFunc) is " << sizeof(udptrFunc) << endl /* 16 bytes*/
         << "sizeof(udptr0) is " << sizeof(udptr0) << endl /* 16 bytes*/
         << "sizeof(udptr1) is " << sizeof(udptr1) << endl /* 16 bytes*/
         << "sizeof(unique_ptr) is " << sizeof(udptrlambda) << endl /* std::unique_ptr => GCC && MSVC => 8 bytes*/
         << "sizeof(utptr0) is " << sizeof(utptr0) << endl /* MSVC => 16 bytes GCC =>  8 bytes*/
         << "sizeof(utptr1) is " << sizeof(utptr1) << endl; /* MSVC => 16 bytes GCC => 16 bytes*/

    return 0;
}