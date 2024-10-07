#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class Complex {
public:
    double real;
    double imag;
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    double magnitude() const {
        return std::sqrt(real * real + imag * imag);
    }

    bool operator!=(const Complex& other) const {
        double values[2] = { real, imag };
        double otherValues[2] = { other.real, other.imag };
        for (int i = 0; i < 2; ++i) {
            if (values[i]!= otherValues[i]) {
                return true;
            }
        }
        return false;
    }

    bool operator<(const Complex& other) const {
        double values[3] = { magnitude(), real, imag };
        double otherValues[3] = { other.magnitude(), other.real, other.imag };
        for (int i = 0; i < 3; ++i) {
            if (values[i] < otherValues[i]) {
                return true;
            }
            else if (values[i] > otherValues[i]) {
                return false;
            }
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real << ", " << c.imag << ")";
        return os;
    }
};

template <typename T>
class Vector {
private:
    std::vector<T> _elem;

public:
    void insert(int pos, const T& elem) {
        if (pos < 0 || pos > _elem.size())
            throw std::out_of_range("Index out of range");
        _elem.insert(_elem.begin() + pos, elem);
    }

    void remove(int pos) {
        if (pos < 0 || pos >= _elem.size())
            throw std::out_of_range("Index out of range");
        _elem.erase(_elem.begin() + pos);
    }

    int size() const {
        return _elem.size();
    }

    T& operator[](int index) {
        return _elem[index];
    }

    const T& operator[](int index) const {
        return _elem[index];
    }

    void unsort() {
        std::random_shuffle(_elem.begin(), _elem.end());
    }

    Vector<T> findInRange(double m1, double m2) const {
        Vector<T> subVec;
        for (const auto& item : _elem) {
            double mod = item.magnitude();
            if (mod >= m1 && mod < m2) {
                subVec.insert(subVec.size(), item);
            }
        }
        return subVec;
    }

    void unique() {
        std::vector<T> uniqueElems;
        for (const auto& elem : _elem) {
            if (std::find(uniqueElems.begin(), uniqueElems.end(), elem) == uniqueElems.end()) {
                uniqueElems.push_back(elem);
            }
        }
        _elem = uniqueElems;
    }

    void sort() {
        std::sort(_elem.begin(), _elem.end());
    }


    template <typename Func>
    void traverse(Func func) {
        for (auto& item : _elem) {
            func(item);
        }
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));
    Vector<Complex> vec;
    for (int i = 0; i < 10; ++i) {
        double real = rand() % 100 - 50;
        double imag = rand() % 100 - 50;
        vec.insert(i, Complex(real, imag));
    }
    vec.unsort();

    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    Complex target(0, 0);
    std::cout << target << std::endl;

    vec.insert(0, Complex(1, 1));
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    vec.remove(0);
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    vec.unique();
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    vec.sort();
    for (int i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    double m1 = 5.0, m2 = 10.0;
    auto subVec = vec.findInRange(m1, m2);
    std::cout << m1 << " and " << m2 << ":\n";
    for (const auto& c : subVec) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    return 0;
}