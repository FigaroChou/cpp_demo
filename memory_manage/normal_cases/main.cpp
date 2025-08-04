//
// Created by 86155 on 2025/8/5.
//

#include "dynamic_array.h"
#include "memory_pool.h"
#include <iostream>

struct Person
{
    Person() = default;
    Person(int age, double height) : age(age), height(height) {}
    int age;
    double height;
};

void normal_case() {
    // malloc free
    // new delete delete []

    // 关于数组
    // 如何调用非无参构造
    try {
        Person *p_arr = new Person[2]{{12, 123.0}, {123, 12313.0}};
        for (int i = 0; i < 2; i++) {
            std::cout << p_arr[i].age << " " << p_arr[i].height << std::endl;
        }
    } catch (std::bad_alloc & e) {
        std::cerr << "malloc fail" << std::endl;
    }
}

void dynamic_array_case() {
    dynamic_array array;
    for (int i = 0; i < 3; i++) {
        array.add(i * 2);
        std::cout << array[i] << std::endl;
        std::cout << "size: " << array.getSize() << std::endl;
    }
}

void memory_case() {
    try{
        memory_pool pool(sizeof (Person), 2);
        Person *p1 = (Person*) pool.allocate();
        p1 = new(p1) Person(23, 123.0);
        std::cout << p1->age << " " << p1->height << std::endl;

        Person *p2 = (Person*) pool.allocate();
        p2 = new(p2) Person(21, 123.0);
        std::cout << p2->age << " " << p2->height << std::endl;

        Person *p3 = (Person*) pool.allocate();

        pool.deallocate(p1);
        pool.deallocate(p2);

    }catch (std::bad_alloc &e) {
        std::cout << "bad alloc" << std::endl;
    }
}

int main() {
//    normal_case();
//    dynamic_array_case();
    memory_case();

    return 0;
}