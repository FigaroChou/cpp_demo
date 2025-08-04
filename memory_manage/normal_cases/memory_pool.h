//
// Created by 86155 on 2025/8/5.
//

#ifndef TEST_MEMORY_POOL_H
#define TEST_MEMORY_POOL_H

#include <iostream>
#include <stack>
class memory_pool {
public:
    memory_pool(size_t objSize, size_t objCount);
    ~memory_pool();
    void* allocate();
    void deallocate(void * ptr);
private:
    size_t objSize;
    size_t objCount;
    std::stack<void*> pool;
};


#endif //TEST_MEMORY_POOL_H
