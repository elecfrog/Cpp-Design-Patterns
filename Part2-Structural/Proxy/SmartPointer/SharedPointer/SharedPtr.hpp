#include <memory>
#include <iostream>
#include <utility>
#include <functional>
#include "RefCount.hpp"
#include "SmartPtrBase.hpp"

namespace elf {
    template<typename T>
    struct SharedPtr : public SmartPtrBase<T> {
        using Pointer = T *;

        // Constructs a SharedPtr managing the raw pointer passed
        explicit SharedPtr(Pointer ptr = nullptr) : SmartPtrBase<T>(ptr) {}

        // Copy constructor: initializes from another SharedPtr
        // and increments the reference count
        SharedPtr(const SharedPtr &other) {
            copyConstructFrom(other);
        }

        // Templated copy and move constructors for enabling
        // polymorphic behavior and allowing construction from SharedPtr to other types
        template<class U>
        explicit SharedPtr(const SharedPtr<U> &other) {
            copyConstructFrom(other);
        }

        // Move constructor: acquires the resources from another SharedPtr
        // and leaves it in a valid but unspecified state
        SharedPtr(SharedPtr &&other) noexcept {
            moveConstructFrom(std::move(other));
        }

        template<class U>
        explicit SharedPtr(SharedPtr<U> &&other) {
            moveConstructFrom(std::move(other));
        }
        
        // Assignment operators: implemented in terms of the copy-and-swap idiom
        SharedPtr &operator=(SharedPtr &other) {
            other.swap(*this);
            return *this;
        }

        template<class U>
        SharedPtr &operator=(SharedPtr<U> &other) {
            SharedPtr<U>(std::move(other)).swap(*this);
            return *this;
        }

        // Destructor: decrements the reference count and
        // deletes the managed object and the control block if the count reaches zero
        ~SharedPtr() {
            if (this->refCount) {
                this->refCount->decreaseSharedCount();
            }
        }

        // Dereference operator: provides access to the underlying object
        T &operator*() const { return *this->raw; }

        // Arrow operator: allows member access on the underlying object
        Pointer operator->() const { return this->raw; }

        // Conversion operator: allows SharedPtr to be used in boolean contexts
        explicit operator bool() const { return this->raw; }

        // Returns the raw pointer managed by the SharedPtr
        Pointer get() const override {
            return SmartPtrBase<T>::get();
        }
    };

    // Function template for dynamic_pointer_cast, enables casting SharedPtr objects polymorphic
    template<typename T, typename U>
    SharedPtr<T> dynamic_pointer_cast(const SharedPtr<U>& other) {
        auto ptr = dynamic_cast<T*>(other.get());
        return ptr ? SharedPtr<T>(ptr) : SharedPtr<T>();  // Updated constructor call
    }
}
