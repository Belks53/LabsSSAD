#include <iostream>
#include <vector>


template <typename T>
class CircularBuffer {
private:
    std::vector<T> buffer;
    size_t head = 0;
    size_t tail = 0;
    size_t count = 0;
    size_t capacity;

public:
    CircularBuffer(size_t capacity_) : capacity(capacity_) {
        buffer.resize(capacity);
    }

    bool empty() {
        return count == 0;
    }

    void push(const T& item) {
        buffer[tail] = item;
        tail = (tail + 1) % capacity;
        if (tail < capacity) {
            ++count;
        } else {
            head = (head + 1) % capacity;
        }
    }

    T pop() {
        if (empty()) {
            throw std::out_of_range("Empty buffer");
        }
        T item = buffer[head];
        head = (head + 1) % capacity;
        --count;
        return item;
    }

    int size() {
        return count;
    }

    class Iterator {
        CircularBuffer<T>* cb;
        size_t index;
        size_t iterated;

        public:
        Iterator(const CircularBuffer<T>* cb_, size_t start)
            : cb(cb_), index(start), iterated(0) {}

        T& operator*() const {
            return const_cast<T&>(cb->buffer[index]);
        }
        Iterator& operator++() {
            if (cb->count == 0) return *this;
            index = (index + 1) % cb->capacity;
            ++iterated;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return iterated != other.iterated;
        }
    };

    Iterator begin() {
        return Iterator(this, head);
    }

    Iterator end() {
        Iterator iter = Iterator(this, head);
        iter.iterated = count;
        return iter;
    }
};

int main() {
    CircularBuffer<int> cb(10);

    cb.push(1);
    cb.push(2);
    cb.push(3);
    cb.push(4);

    std::cout << cb.size() << std::endl;
    std::cout << cb.pop() << std::endl;
    std::cout << cb.pop() << std::endl;
    std::cout << cb.pop() << std::endl;
    std::cout << cb.pop() << std::endl;
    std::cout << cb.size() << std::endl;
}