#include <iostream>
#include <string>
#include <stack>
#include <unordered_set>
#include <unordered_map>

struct bracket {
    size_t pos;
    char b;
    char _pad[7];
    bracket(size_t pos_, char b_): pos(pos_), b(b_) {}
};

int main() {
    std::string input;
    std::cin >> input;
    std::stack<bracket> stack;
    std::unordered_set<char> non_trivial = {'(', ')', '[', ']', '{', '}'};
    std::unordered_set<char> brackets_open = { '(', '[', '{' };
    std::unordered_map<char, char> brackets_rev = { {')', '('}, {']', '['}, {'}', '{'} };
    for (size_t i = 0; i < input.size(); i++) {
        const char a = input[i];
        if (non_trivial.count(a) == 0) {
            continue;
        }
        if (brackets_open.count(a) != 0) {
            stack.push(bracket(i + 1, a));
        } else {
            if (stack.empty()) {
                std::cout << i + 1 << std::endl;
                return 0;
            }
            if (stack.top().b == brackets_rev[a]) {
                stack.pop();
            } else {
                std::cout << i + 1 << std::endl;
                return 0;
            }
        }
    }
    if (!stack.empty()) {
        auto last = stack.top();
        while (!stack.empty()) {
            last = stack.top();
            stack.pop();
        }
        std::cout << last.pos << std::endl;
    } else {
        std::cout << "Success" << std::endl;
    }
    return 0;
}
