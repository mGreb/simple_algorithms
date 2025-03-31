#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <optional>

class stack_with_max {
private:
    std::stack<std::pair<int, int>> data;  // { val, max }
public:
    stack_with_max(): data() {}
    void push(int val) {
        data.push({val, data.empty() ? val : std::max(data.top().second, val)});
    }
    void pop() {
        if (!data.empty()) {
            data.pop();
        }
    }
    int max() { return data.empty() ? 0 : data.top().second; }
    size_t size() { return data.size(); }
    bool empty() { return data.empty(); }
    int top() { return data.top().first; }
};

class queue_with_max {
private:
    std::queue<int> data;
    stack_with_max left, right;
    size_t window_size;
public:
    queue_with_max(size_t window_size_): data(), left(), right(), window_size(window_size_) {}
    bool empty() { return data.empty(); }
    void push(int val) {  // push also pops if window size is exceeded
        data.push(val);
        if (left.size() == window_size) {
            while (!left.empty()) {
                right.push(left.top());
                left.pop();
            }
        }
        left.push(val);
        right.pop();
        if (data.size() > window_size) {
            data.pop();
        }
    }
    std::optional<int> max() {
        if (data.size() < window_size) {
            return {};
        }
        return std::max(left.max(), right.max());
    }
};

void cout_optional_if_has_value(const std::optional<int>& opt) {
    if (opt.has_value()) {
        std::cout << opt.value() << " ";
    }
}

int main() {
    int len;
    std::cin >> len;
    std::vector<int> data(len);
    for (size_t i = 0; i < data.size(); ++i) {
        std::cin >> data[i];
    }
    int w_size;
    std::cin >> w_size;
    queue_with_max q_m(w_size);
    cout_optional_if_has_value(q_m.max());
    for (size_t i = 0; i < data.size(); ++i) {
        q_m.push(data[i]);
        cout_optional_if_has_value(q_m.max());
    }
    std::cout << std::endl;
    return 0;
}
