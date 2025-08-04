//
// Created by 86155 on 2025/8/5.
//

#include "memory_pool.h"

memory_pool::memory_pool(size_t objSize, size_t objCount)
: objSize(objSize), objCount(objCount)
{
    for (int i = 0; i < objCount; ++i) {
        pool.push(new char[objSize]);
    }
}

void* memory_pool::allocate() {
    if (pool.empty()) {
        throw std::bad_alloc{};
    }
    void *ret = pool.top();
    pool.pop();
    return ret;
}

void memory_pool::deallocate(void * ptr) {
    pool.push(ptr);
}

memory_pool::~memory_pool() {
    while (!pool.empty()) {
        delete[] (char *)pool.top();
        pool.pop();
    }

    std::cout << "done" << std::endl;
}
