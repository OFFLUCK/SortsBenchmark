#ifndef THW_SORTS_HPP
#define THW_SORTS_HPP

#include <iostream>
#include <vector>
#include <utility>

/**
 * @brief - Outputs the array.
 * @param len - Array length.
 * @param arr
 */
void output(size_t len, std::vector<int> const &arr);

/**
 * @brief - Checks if array is sorted.
 * @param arr - Constant array's reference.
 * @return - Verdict.
 */
bool isSorted(std::vector<int> const &arr);

/**
 * @brief - Checks if was array fill is the same as now array fill. Warning: based on unstable counting sort.
 * @param was - Array before sort.
 * @param now - Array after sort.
 * @return - Verdict.
 */
bool checkArraysElementsEquality(std::vector<int> const &was, std::vector<int> const &now);

std::pair<std::vector<int>, uint64_t> bubbleSort(size_t len, std::vector<int> arr);

std::pair<std::vector<int>, uint64_t> bubbleIversonOneSort(size_t len, std::vector<int> arr);

std::pair<std::vector<int>, uint64_t> bubbleIversonOneAndTwoSort(size_t len, std::vector<int> arr);

std::pair<std::vector<int>, uint64_t> selectionSort(size_t len, std::vector<int> arr);

std::pair<std::vector<int>, uint64_t> linearInsertionSort(size_t len, std::vector<int> arr);

std::pair<std::vector<int>, uint64_t> binaryInsertionSort(size_t len, std::vector<int> arr);

std::pair<std::vector<int>, uint64_t> countingSort(size_t len, std::vector<int> arr);

std::pair<std::vector<int>, uint64_t> radixSort(size_t len, std::vector<int> arr);

std::pair<std::vector<int>, uint64_t> mergeSort(size_t len, std::vector<int> arr);

std::pair<std::vector<int>, uint64_t> hoarSort(size_t len, std::vector<int> arr);

std::pair<std::vector<int>, uint64_t> lomutoSort(size_t len, std::vector<int> arr);

std::pair<std::vector<int>, uint64_t> heapSort(size_t len, std::vector<int> arr);

#endif
