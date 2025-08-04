//
// Created by 86155 on 2025/8/5.
//

#ifndef TEST_DYNAMIC_ARRAY_H
#define TEST_DYNAMIC_ARRAY_H

#include <iostream>

class dynamic_array {
public:
    dynamic_array();
    ~dynamic_array();
    void add(int val);
    size_t getSize() const;

    int operator[](size_t idx) const;
private:
    void ensureCapacity();
    void rangeCheck(size_t idx) const;

    size_t capacity;
    size_t size;
    int *array;
};


#endif //TEST_DYNAMIC_ARRAY_H
