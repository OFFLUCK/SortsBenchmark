#include "sorts.hpp"

std::pair<std::vector<int>, int64_t> bubbleSort(size_t len, std::vector<int> arr) {
    int64_t steps = 0;

    for (int ind = 0; ind < len; ++ind) {
        for (int j = 0; j < len - ind - 1; ++j) {
            ++steps;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }

    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, int64_t> bubbleIversonOneSort(size_t len, std::vector<int> arr) {
    // TODO{Mike}
    int64_t steps = 0;
    bool has_swaps;

    for (int ind = 0; ind < len; ++ind) {
        has_swaps = false;

        for (int j = 0; j < len - ind - 1; ++j) {
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

    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, int64_t> bubbleIversonOneAndTwoSort(size_t len, std::vector<int> arr) {
    // TODO{Mike}
    int64_t steps = 0;
    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, int64_t> selectionSort(size_t len, std::vector<int> arr) {
    int min_ind;
    int64_t steps = 0;

    for (int i = 0; i < len - 1; ++i) {
        min_ind = i;
        for (int j = i + 1; j < len; ++j) {
            ++steps;
            if (arr[j] < arr[min_ind]) {
                min_ind = j;
            }
        }
        std::swap(arr[i], arr[min_ind]);
    }

    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, int64_t> linearInsertionSort(size_t len, std::vector<int> arr) {
    int64_t steps = 0;

    for (int i = 1; i < len; ++i) {
        int j = i - 1;
        while ((j > -1) && (arr[j] > arr[j + 1])) {
            ++steps;
            std::swap(arr[j], arr[j + 1]);
            --j;
        }
    }

    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, int64_t> binaryInsertionSort(size_t len, std::vector<int> arr) {
    int64_t steps = 0;
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

    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, int64_t> countingSort(size_t len, std::vector<int> arr) {
    // TODO{Oleg}
    int64_t steps = 0;
    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, int64_t> radixSort(size_t len, std::vector<int> arr) {
    int64_t steps = 0;
    int64_t two_power = 1;
    std::vector<int> new_arr;

    for (int index = 0; index < 31; ++index) {
        new_arr.clear();
        for (int i = 0; i < len; ++i) {
            ++steps;
            if ((arr[i] & two_power) == 0) {
                new_arr.push_back(arr[i]);
            }
        }
        for (int i = 0; i < len; ++i) {
            ++steps;
            if (arr[i] & two_power) {
                new_arr.push_back(arr[i]);
            }
        }
        arr = new_arr;
        two_power *= 2;
    }

    return std::make_pair(arr, steps);
}

std::vector<int> merge(size_t len1, std::vector<int> arr1, size_t len2, std::vector<int> arr2) {
    int point1 = 0;
    int point2 = 0;
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

std::pair<std::vector<int>, int64_t> mergeSort(size_t len, std::vector<int> arr) {
    int64_t steps = 0;

    if (len == 1) {
        return std::make_pair(arr, 1);
    }

    std::vector<int>::const_iterator begin = arr.begin();
    std::vector<int>::const_iterator middle = arr.begin() + len / 2;
    std::vector<int>::const_iterator end = arr.end();
    std::vector<int> first(begin, middle);
    std::vector<int> second(middle, end);

    std::pair<std::vector<int>, int64_t> first_ans = mergeSort(first.size(), first);
    std::pair<std::vector<int>, int64_t> second_ans = mergeSort(first.size(), first);

    first = first_ans.first;
    second = second_ans.first;
    steps += first_ans.second + second_ans.second;

    return std::make_pair(merge(first.size(), first, second.size(), second), steps);
}

std::pair<std::vector<int>, int64_t> hoarSort(size_t len, std::vector<int> arr) {
    // TODO{Mike}
    int64_t steps = 0;
    return std::make_pair(arr, steps);
}

std::pair<std::vector<int>, int64_t> lomutoSort(size_t len, std::vector<int> arr) {
    // TODO{Mike}
    int64_t steps = 0;
    return std::make_pair(arr, steps);
}

void heapBuild(size_t len, int ind, std::vector<int> *arr) {
    int big_elem = ind;
    int left = 2 * big_elem + 1;
    int right = 2 * big_elem + 2;

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

std::pair<std::vector<int>, int64_t> heapSort(size_t len, std::vector<int> arr) {
    int64_t steps = 0;

    for (int i = len / 2 - 1; i > -1; --i) {
        heapBuild(len, i, &arr);
    }

    for (int i = len - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapBuild(i, 0, &arr);
    }

    return std::make_pair(arr, steps);
}
