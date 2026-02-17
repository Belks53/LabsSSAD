#include <iostream>
#include <memory>

#include <ostream>
class Box {
  public:
  int element;

  Box(int e) {
    this->element = e;
  }

  ~Box() {
    std::cout << "Box destructor" << std::endl;
  }

  int getElement() {
    return this->element;
  }

  void setElement(int e) {
    this->element = e;
  }
};

int create_unique(int element) {
  std::unique_ptr<Box> ptr1 = std::make_unique<Box>(element);
  std::unique_ptr<Box> ptr2 = std::move(ptr1);

  return ptr2->getElement();
}

void demonstrate_unique() {
  auto box1 = std::make_unique<Box>(100);
  auto box2 = std::move(box1);

  if (!box1) std::cout << "box1 empty" << std::endl;
  box2->setElement(200);
}

int create_shared_boxes() {
  std::shared_ptr<Box> ptr1 = std::make_shared<Box>(1);
  std::shared_ptr<Box> ptr2 = std::make_shared<Box>(2);

  std::cout << ptr1.use_count() << std::endl;

  auto ptr3 = ptr1;
  std::cout << ptr3.use_count() << std::endl;

  {
    auto ptr4 = ptr1;
    std::cout << "ptr1 use_count inside: " << ptr1.use_count() << std::endl;
  }

  std::cout << "ptr1 use_count after: " << ptr1.use_count() << std::endl;
}

void weak_ptr_dem() {
  std::shared_ptr<Box> ptr1 = std::make_shared<Box>(9999);
  std::weak_ptr<Box> weakPtr = ptr1;

  std::cout << "sharedPtr use_count: " << ptr1.use_count() << std::endl;

  if (!weakPtr.expired()) {
    auto tempShared = weakPtr.lock();
    std::cout << "weak_ptr: " << tempShared->getElement() << std::endl;
    std::cout << "tempShared use_count: " << tempShared.use_count() << std::endl;
  }

  ptr1.reset();

  if (weakPtr.expired()) {
    std::cout << "weakPtr desrtoid" << std::endl;
  }
}

struct N {
  int something;
  std::shared_ptr<N> ptr;

  explicit N(int something) : something(something) {}

  ~N() {
    std::cout << "N destructor" << std::endl;
  }
};

struct SafeN {
  int something;
  std::shared_ptr<SafeN> ptr;
  std::weak_ptr<SafeN> weakPtr;

  explicit SafeN(int something) : something(something) {}

  ~SafeN() {
    std::cout << "S destructor" << std::endl;
  }
};

void demonstrate() {
  {
    std::shared_ptr<N> node1 = std::make_shared<N>(1);
    std::shared_ptr<N> node2 = std::make_shared<N>(2);

    node1->ptr = node2;
    node2->ptr = node1;
  }

  {
    auto node1 = std::make_shared<SafeN>(1);
    auto node2 = std::make_shared<SafeN>(2);

    node1->ptr = node2;
    node2->weakPtr = node1;

    node2->ptr = node1;
    node1->weakPtr = node2;
  }
}

int main() {
  std::cout << "UNIQUE" << std::endl;
  int val = create_unique(42);
  std::cout << val << std::endl;
  demonstrate_unique();

  std::cout << "\nSHARED" << std::endl;
  create_shared_boxes();

  std::cout << "\nWEAK" << std::endl;
  weak_ptr_dem();

  std::cout << "\n" << std::endl;
  demonstrate();
}