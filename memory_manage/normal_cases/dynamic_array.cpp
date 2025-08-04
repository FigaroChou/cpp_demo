//
// Created by 86155 on 2025/8/5.
//

#include "dynamic_array.h"

dynamic_array::dynamic_array()
: capacity(2), size(0), array(new(std::nothrow) int[capacity])
{
    if (array == nullptr) {
        throw std::bad_alloc{};
    }
}

void dynamic_array::add(int val) {
    ensureCapacity();
    array[size++] = val;
}

void dynamic_array::ensureCapacity() {
    if (size < capacity) {
        return;
    }

    array = (int *) realloc(array, capacity * 2);
    if (array == nullptr) {
        throw std::bad_alloc{};
    }

    capacity = 2 * capacity;
}

size_t dynamic_array::getSize() const {
    return size;
}

int dynamic_array::operator[](size_t idx) const {
    rangeCheck(idx);
    return array[idx];
}

void dynamic_array::rangeCheck(size_t idx) const {
    if (idx >= size) {
        throw std::out_of_range{&"idx: " [ idx]};
    }
}

dynamic_array::~dynamic_array() {
    delete [] array;
}

