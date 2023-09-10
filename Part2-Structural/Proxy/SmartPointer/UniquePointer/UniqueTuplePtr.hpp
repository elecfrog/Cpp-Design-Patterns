/*
 * description: minial unique_ptr with deleter and EBO
 * author@elecfrog
 */
#pragma once
#pragma once

#include <utility>
#include <tuple>

namespace elf {

    template<typename T, typename D>
    class UniqueTuplePtr {
    public:
        // Alias for pointer to T
        using Pointer = T *;
        using Deleter = D;

        // Constructor accepting a raw pointer, defaulting to nullptr
        explicit UniqueTuplePtr(Pointer ptr = nullptr, Deleter deleter = Deleter())
                : compressedPair(ptr, deleter) {}

        // Move constructor allowing transfer of ownership of the managed object
        UniqueTuplePtr(UniqueTuplePtr &&other) noexcept
                : compressedPair(std::move(other.compressedPair)) {
            other.release();
        }

        // Deleting the copy constructor to prevent copying
        UniqueTuplePtr(const UniqueTuplePtr &other) = delete;

        // Deleting the copy assignment operator to prevent copying
        UniqueTuplePtr &operator=(const UniqueTuplePtr &other) = delete;

        // Destructor which deletes the managed object
        ~UniqueTuplePtr() {
            if (get()) {
                getDeleter()(get());
            }
        }

        // Method to reset the managed object, deleting the old object and taking ownership of the new one
        void reset(Pointer other = nullptr) {
            if (get()) {
                getDeleter()(get());
            }
            get() = other;
        }

        // Method to release ownership of the managed object, returning the raw pointer
        Pointer release() {
            Pointer ptr = get();
            get() = nullptr;
            return ptr;
        }

        // Method to get the raw pointer without releasing ownership
        Pointer &get() {
            return std::get<0>(compressedPair);
        }

        // Method to get the raw pointer without releasing ownership
        const Pointer &get() const {
            return std::get<0>(compressedPair);
        }

        // Method to get the deleter without releasing ownership
        Deleter &getDeleter() {
            return std::get<1>(compressedPair);
        }

        // Dereference operator, allowing access to the managed object
        T &operator*() const {
            return *get();
        }

        // Arrow operator, allowing member access on the managed object
        Pointer operator->() const {
            return get();
        }

        // Conversion operator to allow UniqueTuplePtr to be used in boolean contexts
        explicit operator bool() const {
            return get() != nullptr;
        }

        // Templated move constructor allowing transfer of ownership from a UniqueTuplePtr of U to a UniqueTuplePtr of T
        template<class U, class OD>
        explicit UniqueTuplePtr(UniqueTuplePtr<U, OD> &&ptr) noexcept
                : compressedPair(ptr.release(), std::move(ptr.getDeleter())) {}

        // Templated move assignment operator allowing transfer of ownership from a UniqueTuplePtr of U to a UniqueTuplePtr of T
        template<class U, class OD>
        UniqueTuplePtr &operator=(UniqueTuplePtr<U, OD> &&ptr) noexcept {
            reset(ptr.release());
            getDeleter() = std::move(ptr.getDeleter());
            return *this;
        }

    private:
        // Tuple holding the raw pointer and deleter
        std::tuple<Pointer, Deleter> compressedPair;
    };
}
