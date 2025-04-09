#include <iostream>
#include <string>
#include <vector>

template< typename T>
T readT() {
    T val;
    std::cin >> val;
    return val;
}

int main() {
    size_t n;
    std::cin >> n;
    std::vector<std::string> data(10000000, "");
    for (size_t i = 0; i < n; ++i) {
        const auto command = readT<std::string>();
        if (command == "add") {
            const auto num = readT<size_t>();
            const auto name = readT<std::string>();
            data[num] = name;
        }
        if (command == "del") {
            const auto num = readT<size_t>();
            if (!data[num].empty()) {
                data[num] = "";
            }
        }
        if (command == "find") {
            const auto num = readT<size_t>();
            if (!data[num].empty()) {
                std::cout << data[num] << "\n";
            } else {
                std::cout << "not found" << "\n";
            }
        }
    }
    return 0;
}
