// #include <cstring>
// #include <iostream>
// #include <ostream>
//
// template <typename T>
// class Wrapper {
// private:
//     T value;
//
// public:
//     explicit Wrapper(T value) : value(value) {}
//
//     T getValue() {
//         return value;
//     }
// };
//
// template <>
// class Wrapper<const char*> {
// private:
//     const char* value;
//
// public:
//     explicit Wrapper(const char* value) : value(value) {}
//
//     int getValue() {
//         return strlen(value);
//     }
// };
//
// int main() {
//     Wrapper<const char*> b("hello");
//     std::cout << b.getValue() << std::endl;
// }