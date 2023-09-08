/*
 * description: minial unique_ptr with deleter and EBO
 * author@elecfrog
 */
#pragma once

#include <utility>

namespace elf {

    template<typename T, typename D>
    class UniqueDeletePtr {
    public:
        // Alias for pointer to T
        using Pointer = T *;
        using Deleter = D;

        // Constructor accepting a raw pointer, defaulting to nullptr
        explicit UniqueDeletePtr(Pointer ptr = nullptr, Deleter deleter = nullptr)
                : raw(ptr), deleter(deleter) {}

        // Move constructor allowing transfer of ownership of the managed object
        UniqueDeletePtr(UniqueDeletePtr &&other) noexcept
                : raw(other.release()), deleter(std::move(other.deleter)) {}

        // Deleting the copy constructor to prevent copying
        UniqueDeletePtr(const UniqueDeletePtr &other) = delete;

        // Deleting the copy assignment operator to prevent copying
        UniqueDeletePtr &operator=(const UniqueDeletePtr &other) = delete;

        // Destructor which deletes the managed object
        ~UniqueDeletePtr() {
            deleter(raw);
        }

        // Method to reset the managed object, deleting the old object and taking ownership of the new one
        void reset(Pointer other = nullptr) {
            auto oldPtr = raw;
            raw = other;
            deleter(oldPtr);
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

        // Method to get the raw pointer without releasing ownership
        Deleter &getDeleter() const {
            return deleter;
        }

        // Dereference operator, allowing access to the managed object
        T &operator*() const {
            return *raw;
        }

        // Arrow operator, allowing member access on the managed object
        Pointer operator->() const {
            return raw;
        }

        // Conversion operator to allow UniqueDeletePtr to be used in boolean contexts
        explicit operator bool() const {
            return raw;
        }

        // Templated move constructor allowing transfer of ownership from a UniqueDeletePtr of U to a UniqueDeletePtr of T
        template<class U, class OD>
        explicit UniqueDeletePtr(UniqueDeletePtr<U, OD> &&ptr) noexcept
                : raw(ptr.release()), deleter(std::move(ptr.get_deleter())) {}

        // Templated move assignment operator allowing transfer of ownership from a UniqueDeletePtr of U to a UniqueDeletePtr of T
        template<class U, class OD>
        UniqueDeletePtr &operator=(UniqueDeletePtr<U, OD> &&ptr) noexcept {
            reset(ptr.release());
            deleter = std::move(ptr.getDeleter());
            return *this;
        }

    private:
        // The raw pointer to the managed object
        Pointer raw;
        Deleter deleter;
    };
}