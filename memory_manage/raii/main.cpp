//
// Created by 86155 on 2025/8/6.
//

#include "simple_shared_ptr.h"
#include <iostream>

using namespace test;

// 测试类
class Test {
public:
    explicit Test(int val) : value(val) {
        std::cout << "Test Constructor: " << value << std::endl;
    }
    ~Test() {
        std::cout << "Test Destructor: " << value << std::endl;
    }
    void show() const {
        std::cout << "Value: " << value << std::endl;
    }

private:
    int value;
};

void simple_shared_ptr_case() {
    {
        std::cout << "Creating default constructed shared_ptr..." << std::endl;
        simple_shared_ptr<Test> ptr1; // 默认构造
        std::cout << "ptr1 use_count: " << ptr1.use_count() << std::endl; // 0

        std::cout << "\nCreating shared_ptr with resource..." << std::endl;
        simple_shared_ptr<Test> ptr2(new Test(100)); // 非默认构造
        std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl; // 1
        ptr2->show();

        std::cout << "\nCopying ptr2 to ptr3..." << std::endl;
        simple_shared_ptr<Test> ptr3 = ptr2; // 拷贝构造
        std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl; // 2
        std::cout << "ptr3 use_count: " << ptr3.use_count() << std::endl; // 2
        ptr3->show();

        std::cout << "\nAssigning ptr3 to ptr1..." << std::endl;
        ptr1 = ptr3; // 拷贝赋值
        std::cout << "ptr1 use_count: " << ptr1.use_count() << std::endl; // 3
        std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl; // 3
        std::cout << "ptr3 use_count: " << ptr3.use_count() << std::endl; // 3

        std::cout << "\nResetting ptr2..." << std::endl;
        ptr2.reset(new Test(200)); // 重新指向新的对象
        std::cout << "ptr2 use_count: " << ptr2.use_count() << std::endl; // 1
        ptr2->show();
        std::cout << "ptr1 use_count: " << ptr1.use_count() << std::endl; // 2
        std::cout << "ptr3 use_count: " << ptr3.use_count() << std::endl; // 2

        std::cout << "\nExiting scope..." << std::endl;
    }

    // ptr2, ptr1, ptr3 离开作用域
    std::cout << "End of main." << std::endl;
}

int main() {
    simple_shared_ptr_case();
}