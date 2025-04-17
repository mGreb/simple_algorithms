#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <experimental/iterator>
#include <functional>

using node = std::array<int, 4>;
using tree = std::vector<node>;

#define N 0  // node index
#define V 1  // node value
#define L 2  // left child index
#define R 3  // right child index

template<typename T>
T readT() {
    T val;
    std::cin >> val;
    return val;
}

template<typename T>
void printWithDelimiter(const T& v, std::ostream& o, char d = ' ') {
    std::copy(v.begin(), v.end(), std::experimental::make_ostream_joiner(o, d));
    o << "\n";
}

bool isChecking(const tree& t, const std::function<bool(int)>& checker) {
    if (t.empty()) {return true;}
    std::stack<int> s;
    int curr = t[0][N];
    while (curr != -1 || !s.empty()) {
        while (curr != -1) {
            s.push(curr);
            curr = t[(size_t)curr][L];
        }
        curr = s.top();
        s.pop();
        if (!checker(t[(size_t)curr][V])) {
            return false;
        }
        curr = t[(size_t)curr][R];
    }
    return true;
}

int main() {
    const auto n = readT<size_t>();
    tree t(n);
    for (size_t i = 0; i < n; ++i) {
        t[i][N] = (int)i;
        std::cin >> t[i][V] >> t[i][L] >> t[i][R];
    }

    const auto checker = [isPrevValSet = false, prevVal = 0] (int val) mutable {
        if (isPrevValSet && prevVal > val) {
            return false;
        } else {
            prevVal = val;
            isPrevValSet = true;
        }
        return true;
    };

    if (isChecking(t, checker)) {
        std::cout << "CORRECT\n";
    } else {
        std::cout << "INCORRECT\n";
    }

    return 0;
}
