#include <iostream>
#include <ostream>

void swap_pointer(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_reference(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int number1;
    int number2;
    std::cin >> number1 >> number2;
    std::cout << number1 << " " << number2 << std::endl;
    swap_pointer(&number1, &number2);
    std::cout << number1 << " " << number2 << std::endl;
    swap_reference(number1, number2);
    std::cout << number1 << " " << number2 << std::endl;
}

