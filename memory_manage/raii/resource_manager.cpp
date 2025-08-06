//
// Created by 86155 on 2025/8/6.
//

#include "resource_manager.h"

resource_manager::resource_manager(int val)
{
    ptr_ = std::make_unique<int>(val);
}

resource_manager::resource_manager(resource_manager &&other) noexcept
{
    ptr_ = std::move(other.ptr_);
}


resource_manager &resource_manager::operator=(resource_manager &&other) noexcept {
    if (&other == this) {
        return *this;
    }

    ptr_ = std::move(other.ptr_);
    return *this;
}

int resource_manager::getValue() const {
    return *ptr_;
}

void resource_manager::setValue(int newValue) {
    *ptr_ = newValue;
}


