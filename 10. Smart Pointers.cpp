#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass(const std::string& name) : name_(name) {
        std::cout << "MyClass " << name_ << " created.\n";
    }
    ~MyClass() {
        std::cout << "MyClass " << name_ << " destroyed.\n";
    }
private:
    std::string name_;
};

// ------------ Unique Pointer Example ------------

void rawUniqueExample() {
    std::cout << "\n[Raw Pointer - Unique Ownership]\n";
    MyClass* obj = new MyClass("RawUnique");
    // Do something...
    delete obj;  // Must manually delete
}

void smartUniqueExample() {
    std::cout << "\n[unique_ptr Example]\n";
    std::unique_ptr<MyClass> obj = std::make_unique<MyClass>("SmartUnique");
    // Automatically deleted when obj goes out of scope
}

// ------------ Shared Pointer Example ------------

void rawSharedExample() {
    std::cout << "\n[Raw Pointer - Shared Ownership]\n";
    MyClass* obj = new MyClass("RawShared");
    MyClass* shared1 = obj;
    MyClass* shared2 = obj;
    // Need to manually delete, and dangerous if deleted more than once
    delete obj;
}

void smartSharedExample() {
    std::cout << "\n[shared_ptr Example]\n";
    std::shared_ptr<MyClass> shared1 = std::make_shared<MyClass>("SmartShared");
    std::shared_ptr<MyClass> shared2 = shared1; // shared1 and shared2 both own the object
    // Automatically deleted when last owner goes out of scope
}

// ------------ Weak Pointer Example ------------

struct B; // forward declaration

struct A {
    std::shared_ptr<B> b_ptr;
    ~A() { std::cout << "A destroyed\n"; }
};

struct B {
    std::weak_ptr<A> a_ptr; // prevents cyclic reference
    ~B() { std::cout << "B destroyed\n"; }
};

void weakPointerExample() {
    std::cout << "\n[weak_ptr Example to break circular reference]\n";
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    a->b_ptr = b;
    b->a_ptr = a; // does NOT increase reference count
    // When a and b go out of scope, both are properly destroyed
}

int main() {
    rawUniqueExample();
    smartUniqueExample();

    rawSharedExample();
    smartSharedExample();

    weakPointerExample();

    return 0;
}
