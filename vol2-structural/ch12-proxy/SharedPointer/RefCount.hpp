#pragma once

#include <atomic>

namespace elf {
    // Simulates the control block of the shared_ptr and weak_ptr
    struct RefCountBase {
        RefCountBase() : sharedCount(1), weakCount(1) {}

    public:
        RefCountBase(const RefCountBase &) = delete;

        RefCountBase &operator=(const RefCountBase &) = delete;

        // Increases the shared reference count
        void increaseSharedCount() { sharedCount++; }

        // Increases the weak reference count
        void increaseWeakCount() { weakCount++; }

        // Decreases the shared reference count and checks whether the managed object should be destroyed
        void decreaseSharedCount() {
            if (--sharedCount == 0) {
                destroy();
                decreaseWeakCount();
            }
        }

        // Decreases the weak reference count and checks whether the control block should be destroyed
        void decreaseWeakCount() {
            if (--weakCount == 0) {
                deleteSelf();
            }
        }

        // Returns the current shared reference count
        int getSharedCount() const { return sharedCount.load(); }

        // Returns the current weak reference count
        int getWeakCount() const { return weakCount.load(); }

    private:
        std::atomic<int> sharedCount;
        std::atomic<int> weakCount;

        virtual void destroy() noexcept = 0; // destroy managed resource
        virtual void deleteSelf() noexcept = 0; // destroy self
    };


    template<typename T>
    struct RefCount : public RefCountBase {
    public:
        explicit RefCount(T *raw) : RefCountBase(), raw(raw) {}

    private:
        void destroy() noexcept override { // destroy managed resource
            delete raw;
        }

        void deleteSelf() noexcept override { // destroy self
            delete this;
        }

        T *raw;
    };
}