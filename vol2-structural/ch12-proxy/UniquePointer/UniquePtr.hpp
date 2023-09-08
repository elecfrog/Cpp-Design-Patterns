/*
 * description: minial unique_ptr with no deleter
 * author@elecfrog
 */
#pragma once

#include <utility>


namespace elf {

    template<typename T>
    class UniquePtr {
    public:
        // Alias for pointer to T
        using Pointer = T *;

        // Constructor accepting a raw pointer, defaulting to nullptr
        explicit UniquePtr(Pointer ptr = nullptr)
                : raw(ptr) {}

        // Move constructor allowing transfer of ownership of the managed object
        UniquePtr(UniquePtr &&other) noexcept
                : raw(other.release()) {}

        // Deleting the copy constructor to prevent copying
        UniquePtr(const UniquePtr &other) = delete;

        // Deleting the copy assignment operator to prevent copying
        UniquePtr &operator=(const UniquePtr &other) = delete;

        // Destructor which deletes the managed object
        ~UniquePtr() {
            delete raw;
        }

        // Method to reset the managed object, deleting the old object and taking ownership of the new one
        void reset(Pointer other = nullptr) {
            auto oldPtr = raw;
            raw = other;
            delete oldPtr;
        }

        // Method to release ownership of the managed object, returning the raw pointer
        Pointer release() {
            auto ptr = raw;
            raw = nullptr;
            return ptr;
        }

        // Method to get the raw pointer without releasing ownership
        Pointer get() const {
            return raw;
        }

        // Dereference operator, allowing access to the managed object
        T &operator*() const {
            return *raw;
        }

        // Arrow operator, allowing member access on the managed object
        Pointer operator->() const {
            return raw;
        }

        // Conversion operator to allow UniquePtr to be used in boolean contexts
        explicit operator bool() const {
            return raw;
        }

        // Templated move constructor allowing transfer of ownership from a UniquePtr of U to a UniquePtr of T
        template<class U>
        explicit UniquePtr(UniquePtr<U> &&ptr) noexcept {
            raw = ptr.release();
        }

        // Templated move assignment operator allowing transfer of ownership from a UniquePtr of U to a UniquePtr of T
        template<class U>
        UniquePtr &operator=(UniquePtr<U> &&ptr) noexcept {
            reset(ptr.release());
            return *this;
        }

    private:
        // The raw pointer to the managed object
        Pointer raw;
    };
}