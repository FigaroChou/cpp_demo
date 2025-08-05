//
// Created by 86155 on 2025/8/6.
//

#ifndef TEST_SIMPLE_SHARED_PTR_H
#define TEST_SIMPLE_SHARED_PTR_H

#include "Test.h"
#include <iostream>

namespace test {

struct ContextBlock
{
    ContextBlock(): ref_count(1) {}
    size_t ref_count;
};

template<typename T>
class simple_shared_ptr {
public:
    simple_shared_ptr();
    explicit simple_shared_ptr(T * ptr);
    simple_shared_ptr(const simple_shared_ptr<T> &sharedPtr);
    simple_shared_ptr(simple_shared_ptr<T> &&sharedPtr) noexcept;

    ~simple_shared_ptr();

    simple_shared_ptr<T>& operator=(const simple_shared_ptr<T> &sharedPtr);
    simple_shared_ptr<T>& operator=(simple_shared_ptr<T> &&sharedPtr) noexcept;

    T * operator->() const;
    T& operator*() const;

    void reset(T *ptr = nullptr);
    size_t use_count() const;
    T * get() const;
private:
    void release();

    T * ptr_;
    struct ContextBlock * block_;
};

} // namespace test

#endif //TEST_SIMPLE_SHARED_PTR_H
