#ifndef THW_TESTDATASET_HPP
#define THW_TESTDATASET_HPP

#include <vector>

template<typename Action>
struct TestDataset {
    std::vector<int> arr;
    Action update_action;
    Action init_action;
    int resize_step;

    TestDataset(int init_len, int resize_step, Action init_action) {
        this->resize_step = resize_step;
        this->update_action = update_action;
        this->init_action = init_action;
        arr = std::vector<int>(init_len);
        init_action(&arr);
    }

    void update() {
        init_action(&arr);
    }

    void resize() {
        arr.resize(arr.size() + this->resize_step);
        for (int i = 0; i < arr.size(); ++i) {
            arr[i] = i;
        }
    }
};
#endif
