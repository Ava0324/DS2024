#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

class Stack {
public:
    void push(int item) {
        items.push_back(item);
    }

    int pop() {
        if (!is_empty()) {
            int lastItem = items.back();
            items.pop_back();
            return lastItem;
        } else {
            return -1;
        }
    }

    int top() const {
        if (!is_empty()) {
            return items.back();
        } else {
            return -1;
        }
    }

    bool is_empty() const {
        return items.empty();
    }

    int size() const {
        return items.size();
    }

private:
    std::vector<int> items;
};

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

int performOperation(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0) {
                std::cout << "式子无效（除数不能为 0）" << std::endl;
                return -1;
            }
            return a / b;
    }
    return 0;
}

int evaluateExpression(const std::string& expression) {
    Stack values;
    Stack operators;

    for (int i = 0; i < expression.length(); ++i) {
        if (expression[i] == ' ')
            continue;
        else if (expression[i] >= '0' && expression[i] <= '9') {
            std::stringstream ss;
            while (i < expression.length() && expression[i] >= '0' && expression[i] <= '9') {
                ss << expression[i++];
            }
            int num;
            ss >> num;
            values.push(num);
            --i;
        } else if (expression[i] == '(') {
            operators.push(expression[i]);
        } else if (expression[i] == ')') {
            while (!operators.is_empty() && operators.top()!= '(') {
                int val2 = values.pop();
                int val1 = values.pop();
                char op = operators.pop();
                values.push(performOperation(val1, val2, op));
            }
            if (!operators.is_empty())
                operators.pop();
        } else {
            while (!operators.is_empty() && precedence(operators.top()) >= precedence(expression[i])) {
                int val2 = values.pop();
                int val1 = values.pop();
                char op = operators.pop();
                values.push(performOperation(val1, val2, op));
            }
            operators.push(expression[i]);
        }
    }

    while (!operators.is_empty()) {
        int val2 = values.pop();
        int val1 = values.pop();
        char op = operators.pop();
        values.push(performOperation(val1, val2, op));
    }

    return values.top();
}

int precedenceWithTrigLog(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == 's' || op == 'l')
        return 3;
    return 0;
}

int performOperationWithTrigLog(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0) {
                std::cout << "式子无效（除数不能为 0）" << std::endl;
                return -1;
            }
            return a / b;
        case 's':
            return std::sin(b);
        case 'l':
            return std::log(b);
    }
    return 0;
}

int evaluateExpressionWithTrigLog(const std::string& expression) {
    Stack values;
    Stack operators;

    for (int i = 0; i < expression.length(); ++i) {
        if (expression[i] == ' ')
            continue;
        else if (expression[i] >= '0' && expression[i] <= '9') {
            std::stringstream ss;
            while (i < expression.length() && expression[i] >= '0' && expression[i] <= '9') {
                ss << expression[i++];
            }
            int num;
            ss >> num;
            values.push(num);
            --i;
        } else if (expression[i] == '(') {
            operators.push(expression[i]);
        } else if (expression[i] == ')') {
            while (!operators.is_empty() && operators.top()!= '(') {
                int val2 = values.pop();
                int val1 = values.pop();
                char op = operators.pop();
                values.push(performOperationWithTrigLog(val1, val2, op));
            }
            if (!operators.is_empty())
                operators.pop();
        } else {
            if (expression[i] == 's' && expression[i + 1] == 'i' && expression[i + 2] == 'n') {
                operators.push('s');
                i += 2;
            } else if (expression[i] == 'l' && expression[i + 1] == 'o' && expression[i + 2] == 'g') {
                operators.push('l');
                i += 2;
            } else {
                while (!operators.is_empty() && precedenceWithTrigLog(operators.top()) >= precedenceWithTrigLog(expression[i])) {
                    int val2 = values.pop();
                    int val1 = values.pop();
                    char op = operators.pop();
                    values.push(performOperationWithTrigLog(val1, val2, op));
                }
                operators.push(expression[i]);
            }
        }
    }

    while (!operators.is_empty()) {
        int val2 = values.pop();
        int val1 = values.pop();
        char op = operators.pop();
        values.push(performOperationWithTrigLog(val1, val2, op));
    }

    return values.top();
}

int largestRectangleArea(std::vector<int>& heights) {
    int n = heights.size();
    std::vector<int> stack;
    int maxArea = 0;
    int i = 0;
    while (i < n) {
        if (stack.empty() || heights[i] >= heights[stack.back()]) {
            stack.push_back(i++);
        } else {
            int top = stack.back();
            stack.pop_back();
            int width = stack.empty()? i : i - stack.back() - 1;
            int area = heights[top] * width;
            maxArea = std::max(maxArea, area);
        }
    }
    while (!stack.empty()) {
        int top = stack.back();
        stack.pop_back();
        int width = stack.empty()? i : i - stack.back() - 1;
        int area = heights[top] * width;
        maxArea = std::max(maxArea, area);
    }
    return maxArea;
}

int main() {
    // 测试字符串计算器
    std::cout << evaluateExpression("3+4*2") << std::endl;
    std::cout << evaluateExpression("(3+4)*2") << std::endl;
    std::cout << evaluateExpression("5/0") << std::endl;

    // 测试带三角函数和对数的字符串计算器
    std::cout << evaluateExpressionWithTrigLog("sin(30)+log(10)") << std::endl;

    // 测试柱状图最大矩形面积
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < 10; ++i) {
        int n = std::rand() % 105 + 1;
        std::vector<int> heights;
        for (int j = 0; j < n; ++j) {
            heights.push_back(std::rand() % 105);
        }
        std::cout << "输入：";
        for (int h : heights) {
            std::cout << h << " ";
        }
        std::cout << std::endl;
        int area = largestRectangleArea(heights);
        std::cout << "输出：" << area << std::endl;
        std::cout << std::endl;
    }
    return 0;
}