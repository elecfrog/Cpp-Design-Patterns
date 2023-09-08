#include <memory>
#include <iostream>
#include <utility>
#include <functional>

using namespace std;

namespace elf {
    struct SharedCount {
        SharedCount() : count(1) {}

        void AddCount() { count++; }

        int ReduceCount() { return --count; }

        int GetCount() const { return count; }

        int count;
    };

    template<typename T>
    struct ShardProxy {
        using Pointer = T *;

        template<typename U>
        void MoveFrom(::elf::ShardProxy<U> &&other) noexcept {
            raw = other.raw;
            if (raw) {
                other.raw = nullptr;
                sharedCount = other.sharedCount;
            }
        }

        template<typename U>
        void Init(const ::elf::ShardProxy<U> &other) noexcept {
            raw = other.raw;
            if (raw) {
                // other.raw = nullptr;
                sharedCount = other.sharedCount;
                sharedCount->AddCount();
            }
        }


        explicit ShardProxy(Pointer ptr = nullptr) : raw(ptr) {
            if (ptr) { sharedCount = new SharedCount(); }
        }

        ShardProxy(ShardProxy &other) {
            Init(other);
        }

        ShardProxy(ShardProxy &&other) noexcept {
            MoveFrom(move(other));
        }

        template<class U>
        friend
        class ShardProxy;

        template<class U>
        explicit ShardProxy(const ShardProxy<U> &other) {
            Init(other);
        }

        template<class U>
        explicit ShardProxy(ShardProxy<U> &&other) {
            MoveFrom(move(other));
        }

        template<class U>
        explicit ShardProxy(const ShardProxy<U> &other, Pointer ptr) {
            raw = ptr;
            if (raw) {
                sharedCount = other.sharedCount;
                sharedCount->AddCount();
            }
            MoveFrom(move(other));
        }

        void Swap(ShardProxy &other) {
            if (raw) {
                swap(other.raw, raw);
                swap(other.sharedCount, sharedCount);
            }
        }

        ShardProxy &operator=(ShardProxy &other) {
            other.Swap(*this);
            return *this;
        }

        template<class U>
        ShardProxy &operator=(ShardProxy<U> &other) {
            ShardProxy<U>(move(other)).Swap(*this);
            return *this;
        }

        ~ShardProxy() {
            if (raw && !sharedCount->ReduceCount()) {
                delete raw;
                delete sharedCount;
            }
            raw = Pointer();
        }

        T &operator*() const { return *raw; }

        Pointer operator->() const { return raw; }

        explicit operator bool() const { return raw; }

        Pointer Get() const { return raw; }

        int GetCount() const {
            if (!raw) return 0;
            return sharedCount->GetCount();
        }

    private:
        Pointer raw{nullptr};
        SharedCount *sharedCount{nullptr};
    };

    template<typename T, typename U>
    ShardProxy<T> dynamic_pointer_cast(const ShardProxy<U> &other) {
        auto ptr = dynamic_cast<T *>(other.Get());
        return ShardProxy<T>(other.Get());
    }

    template<typename T, typename Deleter /* = std::function<void(T *)>*/>
    struct UniPtr {
        using Pointer = T *;

        // ...
        UniPtr() : raw(nullptr) {}

        explicit UniPtr(Pointer ptr, Deleter deleter /*= [](T *ptr) { delete ptr; }*/)
                : raw(ptr), deleter(deleter) {}

        ~UniPtr() {
            if (raw)
                deleter(raw);
        }

        T *raw;
        Deleter deleter;
    };

    template<typename T, typename Deleter /* = std::function<void(T *)>*/>
    struct TupleUniPtr {
        using Pointer = T *;

        // ...
        TupleUniPtr() = default;

        explicit TupleUniPtr(Pointer ptr, Deleter deleter /*= [](T *ptr) { delete ptr; }*/)
                : compressedPair{ptr, deleter} {}

        ~TupleUniPtr() {
            auto &raw = GetPointer();
            if (raw != nullptr)
                GetDeleter()(raw);

            raw = Pointer();
        }

        Pointer &GetPointer() { return get<0>(compressedPair); }

        Deleter &GetDeleter() { return get<1>(compressedPair); }

        tuple<Pointer, Deleter> compressedPair;
        //        T *raw;
        //        Deleter deleter;
    };
}


void funcDeleter(int *p) { delete p; }

auto deleteLambda = [](int *p) { delete p; };

int main() {

    shared_ptr<int> ptr;

    cout << "sizeof(deleteLambda) is " << sizeof(deleteLambda) << endl
         << "sizeof(&deleterFunction) is " << sizeof(&deleterFunction) << endl;


    return 0;
}