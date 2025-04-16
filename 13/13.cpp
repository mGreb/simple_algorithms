#include <iostream>
#include <vector>
#include <array>
#include <stack>
#include <experimental/iterator>

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
void printWithDelimiter(const T& v, char d = ' ') {
    std::copy(v.begin(), v.end(),
        std::experimental::make_ostream_joiner(std::cout, d));
    std::cout << "\n";
}

std::vector<int> inOrder (const tree& t) {
    std::vector<int> res;
    res.reserve(t.size());
    std::stack<int> s;
    int curr = t[0][N];
    while (curr != -1 || !s.empty()) {
        while (curr != -1) {
            s.push(curr);
            curr = t[(size_t)curr][L];
        }
        curr = s.top();
        s.pop();
        res.push_back(t[(size_t)curr][V]);
        curr = t[(size_t)curr][R];
    }
    return res;
}

std::vector<int> preOrder (const tree& t) {
    std::vector<int> res;
    res.reserve(t.size());
    std::stack<int> s;
    s.push(t[0][N]);
    while (!s.empty()) {
        int curr = s.top();
        s.pop();
        res.push_back(t[(size_t)curr][V]);
        if (t[(size_t)curr][R] != -1) {
            s.push(t[(size_t)curr][R]);
        }
        if (t[(size_t)curr][L] != -1) {
            s.push(t[(size_t)curr][L]);
        }
    }
    return res;
}

std::vector<int> postOrder(const tree& t) {
    std::vector<int> res;
    res.reserve(t.size());
    std::stack<int> s;
    int curr = t[0][N];
    int prev = -1;
    while (curr != -1 || !s.empty()) {
        while (curr != -1) {
            s.push(curr);
            curr = t[(size_t)curr][L];
        }
        curr = s.top();
        if (t[(size_t)curr][R] != -1 && t[(size_t)curr][R] != prev) {
            curr = t[(size_t)curr][R];
        } else {
            res.push_back(t[(size_t)curr][V]);
            prev = curr;
            curr = -1;
            s.pop();
        }
    }
    return res;
}

int main() {
    const auto n = readT<size_t>();
    tree t(n);
    for (size_t i = 0; i < n; ++i) {
        t[i][N] = (int)i;
        std::cin >> t[i][V] >> t[i][L] >> t[i][R];
    }

    printWithDelimiter(inOrder(t));
    printWithDelimiter(preOrder(t));
    printWithDelimiter(postOrder(t));

    return 0;
}
