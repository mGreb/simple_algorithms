#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

class disjointSet {
    std::vector<size_t> data, rank;
public:
    disjointSet(size_t size) {
        data.resize(size);
        rank.resize(size);
        std::iota(data.begin(), data.end(), 0);
    }
    void union_sets(size_t i, size_t j) {
        i = find_set(i);
        j = find_set(j);
        if (i == j) {
            return;
        }
        if (rank[i] < rank[j]) {
            std::swap(rank[i], rank[j]);
        }
        data[j] = i;
        rank[i] += rank[j];
    }
    size_t find_set(size_t i) {
        if (i == data[i]) {
            return i;
        }
        return data[i] = find_set(data[i]);
    }
};

int main() {
    size_t var_cnt, equal_cnt, nequal_cnt;
    std::cin >> var_cnt >> equal_cnt >> nequal_cnt;
    disjointSet ds(var_cnt);
    for (size_t i = 0; i < equal_cnt; ++i) {
        size_t a, b;
        std::cin >> a >> b;
        ds.union_sets(a-1, b-1);
    }
    for (size_t i = 0; i < nequal_cnt; ++i) {
        size_t a, b;
        std::cin >> a >> b;
        if (ds.find_set(a-1) == ds.find_set(b-1)) {
            std::cout << 0 << "\n";
            return 1;
        }
    }
    std::cout << 1 << "\n";
    return 0;
}
