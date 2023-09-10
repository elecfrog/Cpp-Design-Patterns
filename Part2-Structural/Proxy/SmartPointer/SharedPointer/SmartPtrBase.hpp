#pragma once

#include <utility>
#include "RefCount.hpp"

namespace elf {
    template<typename T>
    class SmartPtrBase {
    public:
        using Pointer = T *;

        explicit SmartPtrBase(Pointer ptr = nullptr)
                : raw(ptr) {
            try {
                refCount = ptr ? new RefCount<T>(ptr) : nullptr;
            } catch (...) {
                delete ptr;
                throw;
            }
        }

        virtual ~SmartPtrBase() {
            if (refCount) {
                refCount->decreaseSharedCount();
            }
        }

        SmartPtrBase(const SmartPtrBase &) = delete;

        SmartPtrBase &operator=(const SmartPtrBase &) = delete;

        // Swaps the contents of two SharedPtr objects
        void swap(SmartPtrBase &other) {
            if (raw) {
                std::swap(other.raw, raw);
                std::swap(other.refCount, refCount);
            }
        }

        // Returns the current reference count
        int getSharedCount() const {
            if (!refCount) return 0;
            return refCount->getSharedCount();
        }

    protected:
        virtual Pointer get() const noexcept {
            return raw;
        }

        // Create by r-value, move a new pointer and copy the count  
        template<typename U>
        void moveConstructFrom(SmartPtrBase<U> &&other) noexcept {
            raw = other.raw;
            refCount = other.refCount;

            if (raw) {
                other.raw = nullptr;
                other.refCount = nullptr;
            }
        }

        // Create by l-value, copy a new pointer and copy the count, then increase the count  
        template<typename U>
        void copyConstructFrom(const SmartPtrBase<U> &other) noexcept {
            other.increaseSharedCount();

            this->raw = other.raw;
            this->refCount = other.refCount;
        }

        void increaseSharedCount() const noexcept {
            if (refCount) {
                refCount->increaseSharedCount();
            }
        }


    protected:
        Pointer raw{nullptr};
        RefCount<T> *refCount{nullptr};
    };
}