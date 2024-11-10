#include <iostream>
template <typename T>
class Tree {
private:
    T data;
    Tree<T>* left;
    Tree<T>* right;

public:
    // 构造函数，初始化树节点
    Tree(const T& d) : data(d), left(nullptr), right(nullptr) {}

    // 析构函数，释放树节点内存
    ~Tree() {
        delete left;
        delete right;
    }

    // 判断树是否为空
    bool isEmpty() const {
        return this == nullptr;
    }

    // 插入节点
    void insert(const T& value) {
        if (value < data) {
            if (left == nullptr) {
                left = new Tree(value);
            } else {
                left->insert(value);
            }
        } else {
            if (right == nullptr) {
                right = new Tree(value);
            } else {
                right->insert(value);
            }
        }
    }

    // 查找节点
    bool search(const T& value) const {
        if (data == value) {
            return true;
        } else if (value < data && left!= nullptr) {
            return left->search(value);
        } else if (value > data && right!= nullptr) {
            return right->search(value);
        } else {
            return false;
        }
    }
};
