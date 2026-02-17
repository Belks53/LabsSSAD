#include <iostream>

template <typename T>
class GenericStack{
private:
  int capacity = 10;
  int top;
  T *data;

  public:
  explicit GenericStack(int cap) {
    capacity = cap;
    top = -1;
    data = new T[capacity];
  }

  ~GenericStack() {
    delete[] data;
    capacity = 10;
    top = -1;
  }

  void push(T x) {
    if (top == capacity - 1) {
      resize();
    }
    data[++top] = x;
  }

  T pop(){
    if (top == -1) {
      throw std::out_of_range("Stack is empty");
    }
    T result = data[top];
    data[top].~T();

    top--;
    return result;
  }

  T peek() const {
    if (top == -1) {
      throw std::out_of_range("Stack is empty");
    }
    return data[top];
  }

private:
  void resize() {
    T *new_data = new T[capacity * 2];

    for (int i = 0; i < capacity; i++) {
      new_data[i] = data[i];
    }

    delete[] data;
    data = new_data;
    capacity *= 2;
  }
};

int main() {
  GenericStack<int> a = GenericStack<int>(10);
  a.push(10);
  a.push(20);
  a.push(30);
  std::cout << a.peek() << std::endl;
  std::cout << a.pop() << std::endl;
  std::cout << a.peek() << std::endl;



}