#include <iostream>

template <typename T>
class Queue {
private:
    T* data;
    size_t capacity;
    size_t front;
    size_t rear;
    size_t size;

public:
    Queue(size_t capacity = 10) : capacity(capacity), front(0), rear(capacity - 1), size(0) {
        data = new T[capacity];
    }

    bool isFull() {
        return size == capacity;
    }

    bool isEmpty() {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }

    void push(const T& value) {
        if (isFull()) {
            std::cout << "Queue is full!" << std::endl;
        }
        rear = (rear + 1) % capacity;
        data[rear] = value;
        ++size;
    }

    T pop() {
        if (isEmpty()) {
            std::cout <<"Queue is Empty!" << std::endl;
        }
        T value = data[front];
        front = (front + 1) % capacity;
        --size;
        return value;
    }

    T peek() {
        if (isEmpty()) {
            std::cout <<"Queue is Empty!" << std::endl;
        }
        return data[front];
    }
};

int main() {
    Queue<double> queue(5);

    queue.push(10);
    queue.push(20);
    queue.push(30);
    queue.push(40);
    queue.push(50);

    std::cout << "Front element: " << queue.peek() << std::endl;

    std::cout << "Popped element: " << queue.pop() << std::endl;

    std::cout << "Current queue size: " << queue.getSize() << std::endl;

    while (!queue.isEmpty()) {
        std::cout << "Popped element: " << queue.pop() << std::endl;
    }

    std::cout << "Trying to pop from an empty queue..." << std::endl;
    queue.pop();

    return 0;
}