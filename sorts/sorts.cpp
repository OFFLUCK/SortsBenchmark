#include "sorts.hpp"

std::pair<std::vector<int>, uint64_t> bubbleSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;

    for (size_t ind = 0; ind < len; ++ind) {
        for (size_t j = 0; j < len - ind - 1; ++j) {
            ++steps;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
    isSorted(arr);
    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, uint64_t> bubbleIversonOneSort(size_t len, std::vector<int> arr) {
    // TODO{Mike}
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
    isSorted(arr);
    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, uint64_t> bubbleIversonOneAndTwoSort(size_t len, std::vector<int> arr) {
    // TODO{@OFFLUCK}
    uint64_t steps = 0;
    isSorted(arr);
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
    isSorted(arr);
    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, uint64_t> linearInsertionSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;

    for (size_t i = 1; i < len; ++i) {
        size_t j = i - 1;
        while ((j > -1) && (arr[j] > arr[j + 1])) {
            ++steps;
            std::swap(arr[j], arr[j + 1]);
            --j;
        }
    }
    isSorted(arr);
    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, uint64_t> binaryInsertionSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;
    size_t left;
    size_t right;
    size_t middle;

    for (size_t ind = 1; ind < len; ++ind) {
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

        for (size_t j = ind; j > left; --j) {
            ++steps;
            std::swap(arr[j - 1], arr[j]);
        }
    }
    isSorted(arr);
    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, uint64_t> countingSort(size_t len, std::vector<int> arr) {
    // TODO{@OFFLUCK}
    uint64_t steps = 0;
    isSorted(arr);
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
    isSorted(arr);
    return std::make_pair(arr, steps);
}

std::vector<int> merge(size_t len1, std::vector<int> arr1, size_t len2, std::vector<int> arr2) {
    size_t point1 = 0;
    size_t point2 = 0;
    std::vector<int> ans(len1 + len2);
    while ((point1 < len1) && (point2 < len2)) {
        if (arr1[point1] < arr2[point2]) {
            ans[point1 + point2] = arr1[point1];
            ++point1;
        } else {
            ans[point1 + point2] = arr2[point2];
            ++point2;
        }
    }
    while (point1 < len1) {
        ans[point1 + point2] = arr1[point1];
        ++point1;
    }
    while (point2 < len2) {
        ans[point1 + point2] = arr2[point2];
        ++point2;
    }
    return ans;
}

std::pair<std::vector<int>, uint64_t> mergeSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;

    if (len == 1) {
        isSorted(arr);
        return std::make_pair(arr, 1);
    }

    std::vector<int>::const_iterator begin = arr.begin();
    std::vector<int>::const_iterator middle = arr.begin() + static_cast<int>(len) / 2;
    std::vector<int>::const_iterator end = arr.end();
    std::vector<int> first(begin, middle);
    std::vector<int> second(middle, end);

    std::pair<std::vector<int>, uint64_t> first_ans = mergeSort(first.size(), first);
    std::pair<std::vector<int>, uint64_t> second_ans = mergeSort(first.size(), first);

    first = first_ans.first;
    second = second_ans.first;
    steps += first_ans.second + second_ans.second;
    isSorted(arr);
    return std::make_pair(merge(first.size(), first, second.size(), second), steps);
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

// NOT TESTED!!!
std::pair<std::vector<int>, uint64_t> hoarSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;
    quickHoarSort(&arr, 0, len - 1, &steps);
    isSorted(arr);
    return std::make_pair(arr, steps);
}

int64_t lomutoPartition(std::vector<int> *arr, size_t left, size_t right, uint64_t *steps) {
    ++(*steps);
    int64_t last = (*arr)[right];
    int64_t index = static_cast<int64_t>(left) - 1;
    for (auto i = static_cast<int64_t>(left); i < right; ++i) {
        ++(*steps);
        if ((*arr)[i] <= last) {
            std::swap((*arr)[++index], (*arr)[i]);
        }
    }
    std::swap((*arr)[++index], (*arr)[right]);
    return index;
}

void quickLomutoSort(std::vector<int> *arr, size_t left, size_t right, uint64_t *steps) {
    if ((left < right) && (left > -1)) {
        int64_t part = lomutoPartition(arr, left, right, steps);
        quickLomutoSort(arr, left, part - 1, steps);
        quickLomutoSort(arr, part + 1, right, steps);
    }
}

// NOT TESTED!!!
std::pair<std::vector<int>, uint64_t> lomutoSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;
    quickLomutoSort(&arr, 0, len - 1, &steps);
    isSorted(arr);
    return std::make_pair(arr, steps);
}

void heapBuild(size_t len, size_t ind, std::vector<int> *arr) {
    size_t big_elem = ind;
    size_t left = 2 * big_elem + 1;
    size_t right = 2 * big_elem + 2;

    if (left < len) {
        big_elem = (*arr)[left] > (*arr)[big_elem] ? left : big_elem;
    }

    if (right < len) {
        big_elem = (*arr)[right] > (*arr)[big_elem] ? right : big_elem;
    }

    if (big_elem != ind) {
        std::swap((*arr)[ind], (*arr)[big_elem]);
        heapBuild(len, big_elem, arr);
    }
}

std::pair<std::vector<int>, uint64_t> heapSort(size_t len, std::vector<int> arr) {
    uint64_t steps = 0;

    for (size_t i = len / 2 - 1; i > -1; --i) {
        heapBuild(len, i, &arr);
    }

    for (size_t i = len - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapBuild(i, 0, &arr);
    }
    isSorted(arr);
    return std::make_pair(arr, steps);
}

bool isSorted(std::vector<int> const &arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) {
            std:: cout << arr[i - 1] << ' ' << arr[i] << '\n';
            return false;
        }
    }
    return true;
}
