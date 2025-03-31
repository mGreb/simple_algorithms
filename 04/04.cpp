#include <iostream>
#include <stack>

int main() {
    int ops_num;
    std::cin >> ops_num;
    std::stack<int> numbers, maximum;
    for (int i = 0; i < ops_num; ++i) {
        std::string command;
        std::cin >> command;
        if (command == "pop") {
            numbers.pop();
            maximum.pop();
        }
        if (command == "max") {
            std::cout << (maximum.empty() ? 0 : maximum.top()) << std::endl;
        }
        if (command == "push") {
            int num;
            std::cin >> num;
            maximum.push(maximum.empty() ? num : std::max(maximum.top(), num));
            numbers.push(num);
        }
    }
    return 0;
}
