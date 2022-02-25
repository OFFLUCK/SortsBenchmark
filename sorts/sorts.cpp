#include <iostream>
#include <vector>
#include "sorts.hpp"

constexpr size_t kCountSize = 10000;

void output(size_t len, std::vector<int> const &arr) {
    std::cout << "Array size:" << ' ' << len << '\n';
    for (int i = 0; i < len; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

bool checkArraysElementsEquality(std::vector<int> const &was, std::vector<int> const &now) {
    if (was.size() != now.size()) {
        std::cout << "Size" << '\n';
        return false;
    }

    size_t size = was.size();
    std::vector<int> all_elems_was(kCountSize);
    std::vector<int> all_elems_now(kCountSize);

    for (int i = 0; i < size; ++i) {
        ++all_elems_was[was[i]];
        ++all_elems_now[now[i]];
    }

    for (int i = 0; i < kCountSize; ++i) {
        if (all_elems_was != all_elems_now) {
            std::cout << "Elems" << '\n';
            return false;
        }
    }
    return true;
}

std::pair<std::vector<int>, uint64_t> bubbleSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;

    for (size_t i = 0; i < len; ++i) {
        for (size_t j = 0; j < len - i - 1; ++j) {
            ++steps;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }

    std::cout << isSorted(arr) << '\n';
    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, uint64_t> bubbleIversonOneSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;
    bool has_swaps;

    for (size_t ind = 0; ind < len; ++ind) {
        has_swaps = false;

        for (size_t j = 0; j < len - ind - 1; ++j) {
            ++steps;
            if (arr[j] > arr[j + 1]) {
                has_swaps = true;
                std::swap(arr[j], arr[j + 1]);
            }
        }

        if (!has_swaps) {
            break;
        }
    }

    std::cout << isSorted(arr) << '\n';
    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, uint64_t> bubbleIversonOneAndTwoSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;
    size_t last_index = len;
    size_t curr_last_index;
    bool has_swaps;

    for (size_t i = 0; i < len; ++i) {
        curr_last_index = last_index;
        has_swaps = false;
        for (size_t j = 0; j < std::min(curr_last_index, len - i - 1); ++j) {
            ++steps;
            if (arr[j] > arr[j + 1]) {
                has_swaps = true;
                std::swap(arr[j], arr[j + 1]);
                last_index = j;
            }
        }

        if (!has_swaps) {
            break;
        }
    }

    std::cout << isSorted(arr) << '\n';
    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, uint64_t> selectionSort(size_t len, std::vector<int> arr) {
    size_t min_ind;
    uint64_t steps = 0;

    for (size_t i = 0; i < len - 1; ++i) {
        min_ind = i;
        for (size_t j = i + 1; j < len; ++j) {
            ++steps;
            if (arr[j] < arr[min_ind]) {
                min_ind = j;
            }
        }
        std::swap(arr[i], arr[min_ind]);
    }

    std::cout << isSorted(arr) << '\n';
    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, uint64_t> linearInsertionSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;

    for (int i = 1; i < len; ++i) {
        int j = i - 1;
        while ((j > -1) && (arr[j] > arr[j + 1])) {
            ++steps;
            std::swap(arr[j], arr[j + 1]);
            --j;
        }
    }

    std::cout << isSorted(arr) << '\n';
    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, uint64_t> binaryInsertionSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;
    int left;
    int right;
    int middle;

    for (int ind = 1; ind < len; ++ind) {
        left = 0;
        right = ind - 1;

        while (right - left > -1) {
            ++steps;
            middle = (left + right) / 2;
            if (arr[middle] < arr[ind] + 1) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        for (int j = ind; j > left; --j) {
            ++steps;
            std::swap(arr[j - 1], arr[j]);
        }
    }

    std::cout << isSorted(arr) << '\n';
    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, uint64_t> countingSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;
    std::vector<std::vector<int>> all_nums(kCountSize);

    for (size_t i = 0; i < len; ++i) {
        all_nums[arr[i]].push_back(arr[i]);
    }

    arr.clear();
    arr = std::vector<int>(len);
    size_t pointer = 0;

    for (size_t i = 0; i < kCountSize; ++i) {
        for (size_t j = 0; j < all_nums[i].size(); ++j) {
            arr[pointer] = all_nums[i][j];
            ++pointer;
        }
    }

    std::cout << isSorted(arr) << '\n';
    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, uint64_t> radixSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;
    uint64_t two_power = 1;
    std::vector<int> new_arr;

    for (size_t index = 0; index < 31; ++index) {
        new_arr.clear();
        for (size_t i = 0; i < len; ++i) {
            ++steps;
            if ((arr[i] & two_power) == 0) {
                new_arr.push_back(arr[i]);
            }
        }
        for (size_t i = 0; i < len; ++i) {
            ++steps;
            if (arr[i] & two_power) {
                new_arr.push_back(arr[i]);
            }
        }
        arr = new_arr;
        two_power *= 2;
    }

    std::cout << isSorted(arr) << '\n';
    return std::make_pair(arr, steps);
}

void merge(std::vector<int> *arr, int left_pointer, int middle_pointer, int right_pointer) {
    std::vector<int> first(middle_pointer - left_pointer + 1);
    std::vector<int> second(right_pointer - middle_pointer);

    for (int i = left_pointer; i < middle_pointer + 1; ++i) {
        first[i - left_pointer] = (*arr)[i];
    }

    for (int i = middle_pointer + 1; i < right_pointer + 1; ++i) {
        second[i - middle_pointer - 1] = (*arr)[i];
    }

    int p1 = 0;
    int p2 = 0;
    while ((p1 < first.size()) && (p2 < second.size())) {
        if (first[p1] < second[p2]) {
            (*arr)[left_pointer + p1 + p2] = first[p1];
            ++p1;
        } else {
            (*arr)[left_pointer + p1 + p2] = second[p2];
            ++p2;
        }
    }
    while (p1 < first.size()) {
        (*arr)[left_pointer + p1 + p2] = first[p1];
        ++p1;
    }
    while (p2 < second.size()) {
        (*arr)[left_pointer + p1 + p2] = second[p2];
        ++p2;
    }
}

std::pair<std::vector<int>, uint64_t> mergeSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;
    int current_length;
    int left_pointer;
    int middle_pointer;
    int right_pointer;
    for (current_length = 1; current_length < len; current_length *= 2) {
        for (left_pointer = 0; left_pointer < len - 1; left_pointer += 2 * current_length) {
            middle_pointer = std::min(left_pointer + current_length, static_cast<int>(len)) - 1;
            right_pointer = std::min(left_pointer + 2 * current_length, static_cast<int>(len)) - 1;
            merge(&arr, left_pointer, middle_pointer, right_pointer);
            steps += right_pointer - left_pointer;
        }
    }

    std::cout << isSorted(arr) << '\n';
    return std::make_pair(arr, steps);
}

int64_t hoarPartition(std::vector<int> *arr, size_t left, size_t right, uint64_t *steps) {
    ++(*steps);
    size_t middle_elem = (*arr)[(left + right) / 2];
    int64_t p1 = static_cast<int64_t>(left);
    int64_t p2 = static_cast<int64_t>(right);
    while (p1 <= p2) {
        while ((*arr)[p1] < middle_elem) {
            ++(*steps);
            ++p1;
        }
        while ((*arr)[p2] > middle_elem) {
            ++(*steps);
            --p2;
        }
        if (p1 >= p2) {
            break;
        }
        std::swap((*arr)[p1++], (*arr)[p2--]);
    }
    return p2;
}

void quickHoarSort(std::vector<int> *arr, size_t left, size_t right, uint64_t *steps) {
    if (left < right) {
        int64_t part = hoarPartition(arr, left, right, steps);
        quickHoarSort(arr, left, part, steps);
        quickHoarSort(arr, part + 1, right, steps);
    }
}

std::pair<std::vector<int>, uint64_t> hoarSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;
    quickHoarSort(&arr, 0, len - 1, &steps);

    std::cout << isSorted(arr) << '\n';
    return std::make_pair(arr, steps);
}

int lomutoPartition(std::vector<int> *arr, int left, int right, uint64_t *steps) {
    ++(*steps);
    int last = (*arr)[right];
    int index = left - 1;
    for (int i = left; i < right; ++i) {
        ++(*steps);
        if ((*arr)[i] <= last) {
            std::swap((*arr)[++index], (*arr)[i]);
        }
    }
    std::swap((*arr)[++index], (*arr)[right]);
    return index;
}

void quickLomutoSort(std::vector<int> *arr, int left, int right, uint64_t *steps) {
    if ((left < right) && (left > -1)) {
        int part = lomutoPartition(arr, left, right, steps);
        quickLomutoSort(arr, left, part - 1, steps);
        quickLomutoSort(arr, part + 1, right, steps);
    }
}

std::pair<std::vector<int>, uint64_t> lomutoSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;
    quickLomutoSort(&arr, 0, len - 1, &steps);

    std::cout << isSorted(arr) << '\n';
    return std::make_pair(arr, steps);
}

void heapBuild(size_t len, size_t ind, std::vector<int> *arr) {
    size_t big_elem = ind;
    size_t left = 2 * big_elem + 1;
    size_t right = 2 * big_elem + 2;

    if (left < len) {
        big_elem = arr->at(left) > arr->at(big_elem) ? left : big_elem;
    }

    if (right < len) {
        big_elem = arr->at(right) > arr->at(big_elem) ? right : big_elem;
    }

    if (big_elem != ind) {
        std::swap(arr->at(ind), arr->at(big_elem));
        heapBuild(len, big_elem, arr);
    }
}

std::pair<std::vector<int>, uint64_t> heapSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;

    for (int i = len / 2 - 1; i > -1; --i) {
        heapBuild(len, i, &arr);
    }

    for (int i = len - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapBuild(i, 0, &arr);
    }

    std::cout << isSorted(arr) << '\n';
    return std::make_pair(arr, steps);
}

bool isSorted(std::vector<int> const &arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}
