//
// Created by 86155 on 2025/8/6.
//

#ifndef RAII_PTR_CASES_H
#define RAII_PTR_CASES_H

#endif //RAII_PTR_CASES_H

#include "Test.h"
#include <iostream>
#include <memory>
#include <functional>

class B; // 前向声明

class A {
public:
    std::shared_ptr<B> ptrB;

    A() { std::cout << "A Constructor" << std::endl; }
    ~A() { std::cout << "A Destructor" << std::endl; }
};

class B {
public:
    std::weak_ptr<A> ptrA;

    B() { std::cout << "B Constructor" << std::endl; }
    ~B() { std::cout << "B Destructor" << std::endl; }
};

void unique_ptr_case() {
    // nullptr
    std::unique_ptr<Test> ptr;

    auto test = new Test(1);
    std::unique_ptr<Test> ptr2(test);

    // 没有拷贝语义
    // ptr2 = ptr;
    // std::unique_ptr<Test> ptr3 = ptr2;

    // 移动语义
    // 移动构造
    std::unique_ptr<Test> ptr3 = std::unique_ptr<Test>(test);
    // 移动赋值
    std::unique_ptr<Test> ptr4 = std::move(ptr2);

    // 防止多个unique_ptr指向同一资源
    std::unique_ptr<Test> ptr5 = std::make_unique<Test>(1); // C++ 14
    std::unique_ptr<Test> ptr6(new Test(1));
}

void shared_ptr_case() {
    // 支持 移动语义 拷贝语义 和 之前的 simple_shared_ptr 基本一致

    // 只让资源被智能指针使用
    std::shared_ptr<Test> ptr(new Test(1));
    std::shared_ptr<Test> ptr2 = std::make_shared<Test>(1);
}

void shared_ptr_recycle_ref_case() {
    std::shared_ptr<A> ptrA = std::make_shared<A>();
    std::shared_ptr<B> ptrB = std::make_shared<B>();

    ptrA->ptrB = ptrB;
    ptrB->ptrA = ptrA;

    std::cout << "ptr a count: " << ptrA.use_count() << std::endl;
    std::cout << "ptr b count: " << ptrB.use_count() << std::endl;
    std::cout << "weak ptr a count: " << ptrB->ptrA.use_count() << std::endl;
}

struct FileDeleter {
    void operator()(FILE * f) {
        if (f) {
            std::cout << "close file" << std::endl;
            fclose(f);
        }
    }
};

void deleter(FILE *f) {
    if (f) {
        std::cout << "close file" << std::endl;
        fclose(f);
    }
}

using nothing = void(_iobuf *);
void deleter_in_ptr() {
    std::shared_ptr<FILE> filePtr(fopen("../text.txt", "w"), deleter);
    std::unique_ptr<FILE, std::function<void(_iobuf*)>> uqPtr(fopen("../text.txt", "w"), deleter);
}