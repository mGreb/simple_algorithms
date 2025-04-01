// build min-heap inplace using swaps
#include <iostream>
#include <vector>

std::vector<std::string> result;

void writeSwap(size_t a, size_t b) {
    result.emplace_back(std::to_string(a) + " " + std::to_string(b));
}

void siftDown(std::vector<double>& v, size_t i) {
    const size_t sz = v.size();

    // sift to smaller child
    while (true) {
        const size_t l_i = 2 * i + 1, r_i = 2 * i + 2;
        int min, min_i;
        bool min_selected = false;
        if (l_i < sz) {
            min = v[l_i];
            min_i = l_i;
            min_selected = true;
        }
        if (r_i < sz && v[r_i] < min) {
            min = v[r_i];
            min_i = r_i;
        }
        if (min_selected && min < v[i]) {
            std::swap(v[i], v[min_i]);
            writeSwap(i, min_i);
            i = min_i;
        } else {
            break;
        }
    }
}

void buildHeap(std::vector<double>& v) {
    for (size_t i = v.size() / 2 + 1; i >= 1; --i) {
        siftDown(v, i - 1);
    }
}

int main() {
    size_t len;
    std::cin >> len;
    std::vector<double> data(len);
    for (size_t i = 0; i < data.size(); ++i) {
        std::cin >> data[i];
    }

    buildHeap(data);
    
    std::cout << result.size() << "\n";
    for (const auto& s: result) {
        std::cout << s << "\n";
    }
    
    return 0;
}
