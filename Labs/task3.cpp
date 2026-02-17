//
// Created by Belka1 on 20.01.2026.
//

#include <format>
#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) {
        int num;
        bool flag = true;
        std::cin >> num;
        for (int j = 0; j < n; j++) {
            if (num == arr[j]) {
                flag = false;
            }
        }
        if (flag) {
            arr[i] = num;
            std::cout << num << " ";
        }
    }
    std::cout << std::endl;
    std::cin >> n;
    std::vector<int> v;
    for (int i = 0; i < n; i++) {
        int num;
        std::cin >> num;
        v.push_back(num);
    }
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
    for (auto i:v) {
        std::cout << i << " ";
    }
    return 0;
}
