#include "Base.hpp"
#include <functional>
using namespace test::pojo;

int main()
{ 
    Derived1 base;
    Derived1 derived1;
    Derived2 derived2;

    // reigster
    base.setDerived1Callback(std::bind(&Derived1::printStr, &derived1, "here"));
    base.setDerived2Callback(std::bind(&Derived2::add, &derived2, 1, 2));

    // callback
    base.callDerived1Callback();
    base.callDerived2Callback();

    return 0;
}