// #include <iostream>
// #include <utility>
//
// template <typename T>
// class GenericStack{
// private:
//   int capacity = 10;
//   int top;
//   T *data;
//
//   public:
//   explicit GenericStack(int cap) {
//     capacity = cap;
//     top = -1;
//     data = new T[capacity];
//   }
//
//   ~GenericStack() {
//     delete[] data;
//     capacity = 10;
//     top = -1;
//   }
//
//   virtual void push(T x) {
//     if (top == capacity - 1) {
//       resize();
//     }
//     data[++top] = std::move(x);
//   }
//
//   T pop(){
//     if (top == -1) {
//       throw std::out_of_range("Stack is empty");
//     }
//     T result = data[top];
//     data[top].~T();
//
//     top--;
//     return result;
//   }
//
//   [[nodiscard]] T peek() const {
//     if (top == -1) {
//       throw std::out_of_range("Stack is empty");
//     }
//     return data[top];
//   }
//
//   [[nodiscard]] int size() const {
//     return top+1;
//   }
//
// private:
//   void resize() {
//     T *new_data = new T[capacity * 2];
//
//     for (int i = 0; i < capacity; i++) {
//       new_data[i] = data[i];
//     }
//
//     delete[] data;
//     data = new_data;
//     capacity *= 2;
//   }
// };
//
// class StringStack: public GenericStack<std::string> {
// public:
//   explicit StringStack(int cap) : GenericStack<std::string>(cap) {}
//
//   void push(const std::string x) override {
//     if (x.empty()) {
//       throw std::invalid_argument("String is empty");
//     }
//     GenericStack<std::string>::push(x);
//   }
//
//   void concatTopTwo() {
//     if (this->size() < 2) {
//       throw std::out_of_range("Not enough elements to concat");
//     }
//     std::string s1 = this->pop();
//     std::string s2 = this->pop();
//     std::string s3 = s1 + s2;
//     this->push(s3);
//   }
// };
//
// int main() {
//   try {
//     GenericStack<int> a = GenericStack<int>(10);
//     a.push(10);
//     a.push(20);
//     a.push(30);
//     std::cout << a.peek() << std::endl;
//     std::cout << a.pop() << std::endl;
//     std::cout << a.peek() << std::endl;
//
//     StringStack s = StringStack(10);
//     s.push("bbbb");
//     s.concatTopTwo();
//
//     std::cout << s.peek() << std::endl;
//   } catch (std::exception& e) {
//     std::cout << e.what() << std::endl;
//   }
//
//   return 0;
// }