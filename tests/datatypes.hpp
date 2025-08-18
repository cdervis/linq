#pragma once

#include <string>
#include <vector>

struct person {
    std::string name;
    int         age{};
};

template <typename T>
struct mock_vector : std::vector<T> {
    mock_vector( std::initializer_list<T> list )
        : std::vector<T>( std::move( list ) ) {
    }

    auto begin() {
        ++begin_call_count;
        return std::vector<T>::begin();
    }

    auto begin() const {
        ++begin_call_count;
        return std::vector<T>::begin();
    }

    auto cbegin() const {
        ++begin_call_count;
        return std::vector<T>::cbegin();
    }

    // ReSharper disable once CppMemberFunctionMayBeConst
    void reset_count() {
        begin_call_count = 0;
    }

    mutable int begin_call_count{};
};
