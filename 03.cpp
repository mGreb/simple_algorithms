#include <iostream>
#include <queue>

// return start processing time for each packet
// std queue - push to back, pop from front

int main() {
    int buf_size, packets_num;
    std::cin >> buf_size >> packets_num;
    std::queue<int> queue;
    for (int i = 0; i < packets_num; ++i) {
        int arrival, duration;
        std::cin >> arrival >> duration;
        if (!queue.empty() && queue.front() <= arrival) {
            queue.pop();
        }
        if (queue.size() >= buf_size) {
            std::cout << -1 << std::endl;
        } else {
            const int begin_time = queue.empty() ? arrival : std::max(queue.back(), arrival);
            queue.push(begin_time + duration);
            std::cout << begin_time << std::endl;
        }
    }
    return 0;
}
