#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <ctime>
#include <vector>
#include "sorts/sorts.hpp"

// Sort pointer type.
typedef std::pair<std::vector<int>, uint64_t> (*Func)(size_t len, std::vector<int> arr);
// Random shuffle function pointer type.
typedef void (*UpdateFunc)(std::vector<int> *arr);

// Number of sorts.
constexpr int numOfFuncs = 12;
// Milliseconds in second.
constexpr int milis = 1000;
// constexpr int sortAttempts = 100;
// constexpr int arrLength = 1000;
// Array of sorts' names.
const std::vector<std::string> func_names = {
        "BubbleSort",
        "BubbleSortIverson1",
        "BubbleSortIverson1&2",
        "SelectionSort",
        "LinearInsertionSort",
        "BinaryInsertionSort",
        "CountingSort",
        "RadixSort",
        "MergeSort",
        "HoarSort",
        "LomutoSort",
        "HeapSort",
};
// Array of sorts' pointers.
const std::vector<Func> funcs = {
        bubbleSort,
        bubbleIversonOneSort,
        bubbleIversonOneAndTwoSort,
        selectionSort,
        linearInsertionSort,
        binaryInsertionSort,
        countingSort,
        radixSort,
        mergeSort,
        hoarSort,
        lomutoSort,
        heapSort,
};

/**
 * @brief - Checks if array was sorted and outputs the result.
 * @param testing_arr - input array.
 */
void testIsSorted(std::vector<int> const &testing_arr, int func_index) {
    bool is_sorted = isSorted(testing_arr);
    if (!is_sorted) {
        std::cout << func_names[func_index] << " testIsSorted [-]\n";
        return;
    } else {
        std::cout << func_names[func_index] << " testIsSorted [+]\n";
    }
}

template<typename Action>
struct TestDataset {
    std::vector<int> arr;
    Action update_action;
    Action init_action;
    int resize_step;

    TestDataset(int init_len, int resize_step, Action update_action, Action init_action) {
        this->resize_step = resize_step;
        this->update_action = update_action;
        this->init_action = init_action;
        arr = std::vector<int>(init_len);
        init_action(&arr);
    }

    void update() {
        update_action(&arr);
    }

    void resize() {
        arr.resize(arr.size() + this->resize_step);
        for (int i = 0; i < arr.size(); ++i) {
            arr[i] = i;
        }
    }
};

struct CSVSaver {
    std::vector<double> sort_name_vector;
    std::pair<std::vector<double>, std::vector<double>> rnd_test_small;
    std::pair<std::vector<double>, std::vector<double>> rnd_test_big;
    std::pair<std::vector<double>, std::vector<double>> sorted_test;
    std::pair<std::vector<double>, std::vector<double>> reversed_test;
    std::vector<double> testing_arr_len;

    void write_csv(std::string filename) {
        std::vector<std::pair<std::string, std::vector<double>>> dataset = {
                {"sort_name",          sort_name_vector},
                {"random_time_small",  rnd_test_small.first},
                {"random_steps_small", rnd_test_small.second},
                {"random_time_big",    rnd_test_big.first},
                {"random_steps_big",   rnd_test_big.second},
                {"sorted_time",        sorted_test.first},
                {"sorted_steps",       sorted_test.second},
                {"reversed_time",      reversed_test.first},
                {"reversed_steps",     reversed_test.second},
                {"arr_len",            testing_arr_len}};
        std::ofstream myFile(filename);
        for (int j = 0; j < dataset.size(); ++j) {
            myFile << dataset.at(j).first;
            if (j != dataset.size() - 1)
                myFile << ";";
        }
        myFile << "\n";
        for (int i = 0; i < dataset.at(0).second.size(); ++i) {
            for (int j = 0; j < dataset.size(); ++j) {
                if (j == 0) {
                    myFile << func_names[dataset.at(j).second.at(i)];
                } else {
                    myFile << dataset.at(j).second.at(i);
                }
                if (j != dataset.size() - 1)
                    myFile << ";";
            }
            myFile << "\n";
        }
        myFile.close();
    }
};

/**
 * @brief - Random array test.
 * @param func - sort.
 * @return pair of time and number of operations.
 */
std::pair<double, uint64_t> randomArrayMeasure(std::vector<int> const &random_array, Func func, int func_index) {
    std::vector<int> arr(random_array.size());
    for (int i = 0; i < random_array.size(); ++i) {
        arr[i] = random_array[i];
    }

    clock_t start = clock();
    auto sortRes = func(random_array.size(), arr);
    clock_t end = clock();
    testIsSorted(sortRes.first, func_index);
    return std::make_pair(static_cast<double>(end - start) * milis / CLOCKS_PER_SEC, sortRes.second);
}

/**
 * @brief - Random shuffle of an array.
 * @param arr - array pointer.
 */
void updateRandomArray(std::vector<int> *arr) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(arr->begin(), arr->end(), gen);
}

/**
 * @brief - Creates reverse ordered array.
 * @param arr - array pointer.
 */
void initReversedArray(std::vector<int> *arr) {
    for (int i = 0; i < arr->size(); ++i) {
        arr->at(i) = arr->size() - i;
    }
}

/**
 * @brief - Creates almost sorted array.
 * @param arr - array pointer.
 */
void initNotFullySortedArray(std::vector<int> *arr) {
    std::random_device rd;                       // obtain a random number from hardware
    std::mt19937 gen(rd());                      // seed the generator
    std::uniform_int_distribution<> distr(0, 5); // define the range
    for (int i = 0; i < arr->size(); ++i) {
        arr->at(i) = i;
        if (i > 3 && distr(gen) == 2) {
            arr->at(i) = i - 2;
        }
    }
}

void updateNotFullySortedArray(std::vector<int> *arr) {
    initNotFullySortedArray(arr);
}

void updateReversedArray(std::vector<int> *arr) {
    initReversedArray(arr);
}

void initSmallRandomArray(std::vector<int> *arr) {
    std::random_device rd;
    std::mt19937 gen(rd());
    // Range is set to [0..4].
    std::uniform_int_distribution<> distr(0, 5);

    for (int i = 0; i < arr->size(); ++i) {
        arr->at(i) = distr(gen);
    }
}

void initBigRandomArray(std::vector<int> *arr) {
    std::random_device rd;
    std::mt19937 gen(rd());
    // Range is set to [0..999].
    std::uniform_int_distribution<> distr(0, 4000);

    for (int i = 0; i < arr->size(); ++i) {
        arr->at(i) = distr(gen);
    }
}

struct CheckSortsWorker {
    TestDataset<UpdateFunc> *small_random_array;
    TestDataset<UpdateFunc> *big_random_array;
    TestDataset<UpdateFunc> *not_full_sorted_array;
    TestDataset<UpdateFunc> *reversed_array;
    CSVSaver *csv_saver;
    int initialLen, upperBound;
    int step;
    std::string csvPath;

    CheckSortsWorker(int initialLen, int step, int upperBound, std::string csvPath) {
        this->small_random_array = new TestDataset<UpdateFunc>(initialLen, step, updateRandomArray,
                                                               initSmallRandomArray);
        this->big_random_array = new TestDataset<UpdateFunc>(initialLen, step, updateRandomArray, initBigRandomArray);
        this->not_full_sorted_array = new TestDataset<UpdateFunc>(initialLen, step, updateNotFullySortedArray,
                                                                  initNotFullySortedArray);
        this->reversed_array = new TestDataset<UpdateFunc>(initialLen, step, updateReversedArray, initReversedArray);
        this->initialLen = initialLen;
        this->step = step;
        this->upperBound = upperBound;
        this->csv_saver = new CSVSaver();
        this->csvPath = csvPath;
    }

    void startMeasure() {
        for (size_t j = initialLen; j <= upperBound; j += step) {
            small_random_array->update();
            big_random_array->update();
            not_full_sorted_array->update();
            reversed_array->update();
            for (int i = 0; i < numOfFuncs; ++i) {
                measure(funcs[i], i);
            }
            small_random_array->resize();
            big_random_array->resize();
            not_full_sorted_array->resize();
            reversed_array->resize();
        }
    }

    void measure(Func func, int func_ind) {
        if (small_random_array->arr.size() != big_random_array->arr.size() ||
            big_random_array->arr.size() != reversed_array->arr.size() ||
            big_random_array->arr.size() != not_full_sorted_array->arr.size()) {
            std::cout << "err";
            return;
        }
        csv_saver->sort_name_vector.push_back(func_ind);
        csv_saver->testing_arr_len.push_back(small_random_array->arr.size());
        auto res = randomArrayMeasure(small_random_array->arr, func, func_ind);
        csv_saver->rnd_test_small.first.push_back(res.first);
        csv_saver->rnd_test_small.second.push_back(res.second);
        res = randomArrayMeasure(big_random_array->arr, func, func_ind);
        csv_saver->rnd_test_big.first.push_back(res.first);
        csv_saver->rnd_test_big.second.push_back(res.second);
        sortedArrayMeasure(func, func_ind);
        reverseSortedArrayMeasure(func, func_ind);
    }

    void reverseSortedArrayMeasure(Func func, int func_ind) {
        std::vector<int> arr(this->reversed_array->arr.size());
        for (int i = 0; i < this->reversed_array->arr.size(); ++i) {
            arr[i] = this->reversed_array->arr[i];
        }

        clock_t start = clock();
        auto sortRes = func(this->not_full_sorted_array->arr.size(), arr);
        clock_t end = clock();
        testIsSorted(sortRes.first, func_ind);
        csv_saver->reversed_test.first.push_back(static_cast<double>(end - start) * milis / CLOCKS_PER_SEC);
        csv_saver->reversed_test.second.push_back(sortRes.second);
    }

    void sortedArrayMeasure(Func func, int func_index) {
        std::vector<int> arr(this->not_full_sorted_array->arr.size());
        for (int i = 0; i < this->not_full_sorted_array->arr.size(); ++i) {
            arr[i] = this->not_full_sorted_array->arr[i];
        }

        clock_t start = clock();
        auto sortRes = func(this->not_full_sorted_array->arr.size(), arr);
        clock_t end = clock();
        testIsSorted(sortRes.first, func_index);
        csv_saver->sorted_test.first.push_back(static_cast<double>(end - start) * milis / CLOCKS_PER_SEC);
        csv_saver->sorted_test.second.push_back(sortRes.second);
    }

    void saveCSV() {
        csv_saver->write_csv(csvPath);
    }
};

int main() {
    std::cout << "Start" << '\n';
    auto case1 = new CheckSortsWorker(50, 10, 300, "../docs/case1.csv");
    case1->startMeasure();
    case1->saveCSV();

    auto case2 = new CheckSortsWorker(100, 100, 4100, "../docs/case2.csv");
    case2->startMeasure();
    case2->saveCSV();
    std::cout << "End" << '\n';
//    std::vector<int> arr(1000, 0);
//    std::vector<int> sorted_arr;
//    for (int i = 0; i < arr.size(); ++i) {
//        arr[i] = i;
//    }
//    updateRandomArray(&arr);
//    for (int i = 0; i < numOfFuncs; ++i) {
//        std::cout << func_names[i] << ':' << ' ';
//        sorted_arr = funcs[i](arr.size(), arr).first;
//        output(arr.size(), arr);
//        output(sorted_arr.size(), sorted_arr);
//        std::cout << "Are arrays elements equal: " << checkArraysElementsEquality(arr, sorted_arr) << '\n';
//        std::cout << '\n';
//    }
    return 0;
}
