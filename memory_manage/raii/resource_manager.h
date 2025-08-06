//
// Created by 86155 on 2025/8/6.
//

#ifndef RAII_RESOURCE_MANAGER_H
#define RAII_RESOURCE_MANAGER_H

#include <memory>

class resource_manager {
public:
    explicit resource_manager(int val);

    resource_manager(const resource_manager&) = delete;
    resource_manager& operator=(const resource_manager&) = delete;

    resource_manager(resource_manager&&) noexcept;
    resource_manager& operator=(resource_manager&&) noexcept;

    [[nodiscard]] int getValue() const;
    void setValue(int newValue);
private:
    std::unique_ptr<int> ptr_;
};

#endif //RAII_RESOURCE_MANAGER_H
