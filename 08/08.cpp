#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

class disjointSet {
    std::vector<size_t> data, rank;
    size_t max_rank;
public:
    disjointSet(size_t size, std::vector<size_t> rank_) {
        data.resize(size);
        rank.resize(size);
        std::iota(data.begin(), data.end(), 0);
        rank = std::move(rank_);
        max_rank = *std::max_element(rank.begin(), rank.end());
    }
    auto getMaxRank() {
        return max_rank;
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
        max_rank = std::max(max_rank, rank[i]);
    }
    size_t find_set(size_t i) {
        if (i == data[i]) {
            return i;
        }
        return data[i] = find_set(data[i]);
    }
};

int main() {
    size_t table_cnt, req_cnt;
    std::cin >> table_cnt >> req_cnt;
    std::vector<size_t> table_size(table_cnt);
    for (size_t i = 0; i < table_size.size(); ++i) {
        std::cin >> table_size[i];
    }
    disjointSet ds(table_cnt, table_size);
    for (size_t i = 0; i < req_cnt; ++i) {
        size_t dest, src;
        std::cin >> dest >> src;
        ds.union_sets(dest-1, src-1);
        std::cout << ds.getMaxRank() << "\n";
    }
    return 0;
}
