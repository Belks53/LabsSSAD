//
// Created by Belka1 on 24.02.2026.
//]

#include "task3.h"
#include <vector>
#include <iostream>


std::vector<int> customMap(const std::vector<int>& vec, int (*func)(int)) {
    std::vector<int> result;
    result.reserve(vec.size());

    for (int element : vec) {
        result.push_back(func(element));
    }
    return result;
}

template<typename T, typename Predicate>
std::vector<T> customFilter(const std::vector<T>& input, Predicate pred) {
    std::vector<T> result;

    result.reserve(input.size() / 2);

    for (const auto& element : input) {
        if (pred(element)) {
            result.push_back(element);
        }
    }

    return result;
}

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7};

    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    auto squared = customMap(nums, [](int x) { return x * x; });

    for (int n : squared) std::cout << n << " ";
    std::cout << "\n";

    auto odds = customFilter(nums, [](int x) { return x % 2 != 0; });

    for (int n : odds) std::cout << n << " ";
    std::cout << "\n";

}
