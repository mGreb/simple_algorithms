#include <string>
#include <iostream>
#include <vector>
#include <forward_list>
#include <algorithm>
#include <iterator>
#include <experimental/iterator>

template<typename T>
T readT() {
    T val;
    std::cin >> val;
    return val;
}

size_t hash(const std::string& s, size_t m) {
    static const size_t p = 1'000'000'007;
    static const size_t x = 263;
    size_t res = 0;
    size_t pow = 1;
    for (const auto c: s) {
        res += (size_t)c * pow;
        res %= p;
        pow *= x;
        pow %= p;
    }
    return res % m;
}

int main() {
    const auto m = readT<size_t>();
    std::vector<std::forward_list<std::string>> data(m);
    const auto n = readT<size_t>();

    for (size_t i = 0; i < n; ++i) {
        const auto command = readT<std::string>();
        if (command == "add") {
            const auto s = readT<std::string>();
            auto& fl = data[hash(s, m)];
            if (std::find(fl.begin(), fl.end(), s) == fl.end()) {
                fl.push_front(s);
            }
        }
        if (command == "del") {
            const auto s = readT<std::string>();
            auto& fl = data[hash(s, m)];
            fl.remove(s);
        }
        if (command == "find") {
            const auto s = readT<std::string>();
            auto& fl = data[hash(s, m)];
            auto iter = std::find(fl.begin(), fl.end(), s);
            if (iter == fl.end()) {
                std::cout << "no" << "\n";
            } else {
                std::cout << "yes" << "\n";
            }
        }
        if (command == "check") {
            const auto pos = readT<size_t>();
            auto& fl = data[pos];
            std::copy(fl.begin(), fl.end(),
              std::experimental::make_ostream_joiner(std::cout, " "));
            std::cout << "\n";
        }
    }
    return 0;
}
