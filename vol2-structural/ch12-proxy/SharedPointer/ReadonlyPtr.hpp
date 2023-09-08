#include <memory>
#include <iostream>
#include <utility>
#include <functional>
#include "RefCount.hpp"
#include "SmartPtrBase.hpp"
#include "SharedPtr.hpp"

namespace elf {

    template<typename T>
    class ReadonlyPtr : public SmartPtrBase<T> {
    public:
        using Pointer = T *;

        // Default constructor
        ReadonlyPtr() : SmartPtrBase<T>(nullptr) {}

        // Constructor taking a SharedPtr
        ReadonlyPtr(const SharedPtr<T> &shared_ptr)
                : SmartPtrBase<T>(shared_ptr.get()) { // get method gives raw pointer
            if (this->raw) {
                this->refCount = shared_ptr.refCount; // Copy refCount from SharedPtr
                this->refCount->increaseWeakCount();
            }
        }

        // Copy constructor
        ReadonlyPtr(const ReadonlyPtr &other)
                : SmartPtrBase<T>(other.get()), refCount(other.refCount) { // get method gives raw pointer
            if (this->raw) {
                refCount->increaseWeakCount();
            }
        }

        // Move constructor
        ReadonlyPtr(ReadonlyPtr &&other) noexcept
                : SmartPtrBase<T>(other.get()), refCount(other.refCount) { // get method gives raw pointer
            other.raw = nullptr;
            other.refCount = nullptr;
        }

        // Destructor
        ~ReadonlyPtr() {
            if (refCount) {
                refCount->decreaseWeakCount();
            }
        }

        // Copy assignment operator
        ReadonlyPtr &operator=(const ReadonlyPtr &other) {
            if (&other == this) return *this;

            if (this->refCount) {
                this->refCount->decreaseWeakCount();
            }

            this->raw = other.get(); // get method gives raw pointer
            this->refCount = other.refCount;

            if (this->raw) {
                this->refCount->increaseWeakCount();
            }
            return *this;
        }

        // Move assignment operator
        ReadonlyPtr &operator=(ReadonlyPtr &&other) noexcept {
            this->swap(other);
            return *this;
        }

        // Observing the shared pointer
        SharedPtr<T> lock() const {
            if (this->refCount && this->refCount->getSharedCount() > 0) {
                return SharedPtr<T>(this->raw, this->refCount); // Creating SharedPtr with existing refCount
            }
            return SharedPtr<T>();
        }

    private:
        RefCount<T> *refCount{nullptr};
    };

}
