#pragma once
#include <functional>
#include <iostream>
#include <string>

namespace test::pojo
{
    class Base
    {
    public:
        using Derived1Callback = std::function<void()>;
        using Derived2Callback = std::function<int()>;

        void setDerived1Callback(Derived1Callback &&callback)
        {
            derived1Callback_ = std::move(callback);
        }

        void setDerived2Callback(Derived2Callback &&callback)
        {
            derived2Callback_ = std::move(callback);
        }

        void callDerived1Callback() const
        {
            derived1Callback_();
        }

        void callDerived2Callback() const
        {
            int ret = derived2Callback_();
            std::cout << "ret: " << ret << std::endl;
        }

    private:
        Derived1Callback derived1Callback_;
        Derived2Callback derived2Callback_;
    };

    class Derived1 : public Base
    {
    public:
        void printStr(const std::string &str)
        {
            std::cout << str << std::endl;
        }
    };

    class Derived2 : public Base
    {
    public:
        int add(int v1, int v2) {
            return v1 + v2;
        }
    };
} // namespace test::pojo
