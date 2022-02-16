#include "sorts.hpp"

std::vector<int> bubbleSort(int len, std::vector<int> arr) {
    for (int ind = 0; ind < len; ++ind) {
        for (int j = 0; j < len - ind - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }

    return arr;
}

std::vector<int> bubbleIversonOneSort(int len, std::vector<int> arr) {
    bool has_swaps;

    for (int ind = 0; ind < len; ++ind) {
        has_swaps = false;
        for (int j = 0; j < len - ind - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                has_swaps = true;
                std::swap(arr[j], arr[j + 1]);
            }
        }
        if (!has_swaps) {
            break;
        }
    }

    return arr;
}

std::vector<int> bubbleIversonOneAndTwoSort(int len, std::vector<int> arr) {
    // TODO{}
    return arr;
}

std::vector<int> selectionSort(int len, std::vector<int> arr) {
    int min_ind;
    for (int i = 0; i < len - 1; ++i) {
        min_ind = i;
        for (int j = i + 1; j < len; ++j) {
            if (arr[j] < arr[min_ind]) {
                min_ind = j;
            }
        }
        std::swap(arr[i], arr[min_ind]);
    }

    return arr;
}

std::vector<int> linearInsertionSort(int len, std::vector<int> arr) {
    for (int i = 1; i < len; ++i) {
        int j = i - 1;
        while ((j > -1) && (arr[j] > arr[j + 1])) {
            std::swap(arr[j], arr[j + 1]);
            --j;
        }
    }

    return arr;
}

std::vector<int> binaryInsertionSort(int len, std::vector<int> arr) {
    int left;
    int right;
    int middle;

    for (int ind = 1; ind < len; ++ind) {
        left = 0;
        right = ind - 1;
        while (right - left > -1) {
            middle = (left + right) / 2;
            if (arr[middle] < arr[ind] + 1) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }
        for (int j = ind; j > left; --j) {
            std::swap(arr[j - 1], arr[j]);
        }
    }

    return arr;
}

std::vector<int> countingSort(int len, std::vector<int> arr) {
    // TODO{}
    return arr;
}

std::vector<int> radixSort(int len, std::vector<int> arr) {
    // TODO{}
    return arr;
}

std::vector<int> mergeSort(int len, std::vector<int> arr) {
    // TODO{}
    return arr;
}

std::vector<int> hoarSort(int len, std::vector<int> arr) {
    // TODO{}
    return arr;
}

std::vector<int> lomutoSort(int len, std::vector<int> arr) {
    // TODO{}
    return arr;
}

void heapBuild(int len, int ind, std::vector<int> *arr) {
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

std::vector<int> heapSort(int len, std::vector<int> arr) {
    for (int i = len / 2 - 1; i > -1; --i) {
        heapBuild(len, i, &arr);
    }

    for (int i = len - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapBuild(i, 0, &arr);
    }

    return arr;
}
