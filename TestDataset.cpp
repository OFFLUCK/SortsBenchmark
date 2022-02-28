#include <cstdio>
#include "TestDataset.hpp"

//template<typename Action>
//TestDataset<Action>::TestDataset(int init_len, int resize_step, Action init_action) {
//    this->resize_step = resize_step;
//    this->update_action = update_action;
//    this->init_action = init_action;
//    arr = std::vector<int>(init_len);
//    init_action(&arr);
//}
//
//template<typename Action>
//void TestDataset<Action>::update() {
//    init_action(&arr);
//    // std::cout << arr.size() << '\n';
//    for (size_t i = 0; i < 20; i++) {
//        // std::cout << arr[i] << ' ';
//    }
//    // std::cout << '\n';
//}
//
//template<typename Action>
//void TestDataset<Action>::resize() {
//    arr.resize(arr.size() + this->resize_step);
//    for (int i = 0; i < arr.size(); ++i) {
//        arr[i] = i;
//    }
//}
