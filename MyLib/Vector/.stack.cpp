#include <iostream>

template <typename T>
class Stack {
private:
    T* data;
    int capacity;
    int topIndex;

public:
    // 构造函数，初始化栈的容量
    Stack(int size = 10) : capacity(size), topIndex(-1) {
        data = new T[capacity];
    }

    // 析构函数，释放内存
    ~Stack() {
        delete[] data;
    }

    // 返回栈的大小（元素个数）
    int size() const {
        return topIndex + 1;
    }

    // 判断栈是否为空
    bool empty() const {
        return topIndex == -1;
    }

    // 向栈顶插入元素
    void push(const T& value) {
        if (topIndex == capacity - 1) {
            // 栈已满，可考虑扩容逻辑，这里简单打印提示
            std::cout << "Stack is full. Cannot push." << std::endl;
            return;
        }
        data[++topIndex] = value;
    }

    // 弹出栈顶元素
    void pop() {
        if (empty()) {
            // 栈为空，不能弹出，简单打印提示
            std::cout << "Stack is empty. Cannot pop." << std::endl;
            return;
        }
        --topIndex;
    }

    // 返回栈顶元素的值
    T& top() {
        if (empty()) {
            // 栈为空，抛出异常或进行其他处理，这里简单打印提示并返回一个临时对象（可能导致未定义行为，实际应用应处理好）
            std::cout << "Stack is empty. No top element." << std::endl;
            static T dummy;
            return dummy;
        }
        return data[topIndex];
    }
};