#include <iostream>
#include <vector>
#include <tuple>

struct ProcTime {
    size_t proc_num;
    size_t proc_time;
    bool operator <(const ProcTime& other) {
        if (this->proc_time == other.proc_time) {
            return this->proc_num < other.proc_num;
        } else {
            return this->proc_time < other.proc_time;
        }
    }
};

void siftDown(std::vector<ProcTime>& v, size_t i) {
    const size_t sz = v.size();

    while (true) {
        const size_t l_i = 2 * i + 1, r_i = 2 * i + 2;
        ProcTime min;
        size_t min_i;
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
            i = min_i;
        } else {
            break;
        }
    }
}

int main() {
    size_t proc_cnt, task_cnt;
    std::cin >> proc_cnt >> task_cnt;

    std::vector<ProcTime> heap(proc_cnt);
    for (size_t i = 0; i < heap.size(); ++i) {
        heap[i] = {.proc_num=i, .proc_time=0};
    }

    for (size_t i = 0; i < task_cnt; ++i) {
        size_t task_duration;
        std::cin >> task_duration;
        std::cout << heap[0].proc_num << " " << heap[0].proc_time << "\n";
        heap[0].proc_time += task_duration;
        siftDown(heap, 0);
    }

    return 0;
}
