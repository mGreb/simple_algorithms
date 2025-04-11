#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

// 5
// -1 0 4 0 3
// 4

int main() {
    int num_nodes = 0;
    std::cin >> num_nodes;
    std::unordered_map<int, std::vector<int>> children;
    for (int node_num = 0; node_num < num_nodes; ++node_num) {
        int parent;
        std::cin >> parent;
        children[parent].push_back(node_num);
    }
    std::unordered_map<int, int> depths = {{-1, 0}};
    int max_depth = 0;
    std::stack<int> stack;
    stack.push(-1);
    while (!stack.empty()) {
        const auto num = stack.top();
        stack.pop();
        for (const auto child: children[num]) {
            stack.push(child);
            depths[child] = depths[num] + 1;
            max_depth = std::max(depths[child], max_depth);
        }
    }
    std::cout << max_depth << std::endl;
    return 0;
}
