//
// Created by 86155 on 2025/8/6.
//

#include "simple_shared_ptr.h"

namespace test {
    template<typename T>
    simple_shared_ptr<T>::simple_shared_ptr()
    : ptr_(nullptr), block_(nullptr) {}

    template<typename T>
    simple_shared_ptr<T>::simple_shared_ptr(T *ptr)
    : ptr_(ptr)
    {
        if (ptr) {
            block_ = new ContextBlock();
        } else {
            block_ = nullptr;
        }
    }

    template<typename T>
    simple_shared_ptr<T>::simple_shared_ptr(const simple_shared_ptr<T> &sharedPtr)
    : ptr_(sharedPtr.ptr_)
    {
        if (ptr_) {
            block_ = sharedPtr.block_;
            block_->ref_count++;
        } else {
            block_ = nullptr;
        }
    }

    template<typename T>
    simple_shared_ptr<T>::simple_shared_ptr(simple_shared_ptr<T> &&sharedPtr) noexcept
    : ptr_(sharedPtr.ptr_), block_(sharedPtr.block_)
    {
        sharedPtr.ptr_ = nullptr;
        sharedPtr.block_ = nullptr;
    }

    template<typename T>
    simple_shared_ptr<T> &simple_shared_ptr<T>::operator=(const simple_shared_ptr<T> &sharedPtr)
    {
        // 同对象
        if (this == &sharedPtr) {
            return *this;
        }

        // 指向了相同指针
        if (ptr_ == sharedPtr.ptr_) {
            return *this;
        }

        release();
        ptr_ = sharedPtr.ptr_;
        block_ = sharedPtr.block_;
        if (sharedPtr.ptr_ != nullptr) {
            block_->ref_count++;
        }

        return *this;
    }

    template<typename T>
    simple_shared_ptr<T> &simple_shared_ptr<T>::operator=(simple_shared_ptr<T> &&sharedPtr) noexcept
    {
        if (this == &sharedPtr) {
            return *this;
        }

        // 指向了相同指针
        if (ptr_ == sharedPtr.ptr_) {
            return *this;
        }

        release();
        ptr_ = sharedPtr.ptr_;
        block_ = sharedPtr.block_;

        sharedPtr.ptr_ = nullptr;
        sharedPtr.block_ = nullptr;
        return *this;
    }

    template<typename T>
    simple_shared_ptr<T>::~simple_shared_ptr() {
        release();
    }

    template<typename T>
    T *simple_shared_ptr<T>::operator->() const {
        return ptr_;
    }

    template<typename T>
    T &simple_shared_ptr<T>::operator*() const {
        if (ptr_ == nullptr) {
            throw std::runtime_error("null pointer exception");
        }
        return *ptr_;
    }

    template<typename T>
    void simple_shared_ptr<T>::reset(T *ptr) {
        release();
        ptr_ = ptr;
        if (ptr) {
            block_ = new ContextBlock();
        } else {
            block_ = nullptr;
        }
    }

    template<typename T>
    size_t simple_shared_ptr<T>::use_count() const {
        return block_ == nullptr ? 0 : block_->ref_count;
    }

    template<typename T>
    T *simple_shared_ptr<T>::get() const {
        return ptr_;
    }

    template<typename T>
    void simple_shared_ptr<T>::release()
    {
        if (block_ != nullptr) {
            block_->ref_count--;
            if (block_->ref_count == 0) {
                delete ptr_;
                delete block_;
            }
        }

        ptr_ = nullptr;
        block_ = nullptr;
    }

    template class simple_shared_ptr<Test>;
} // namespace test