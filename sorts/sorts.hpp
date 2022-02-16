#ifndef THW_SORTS_HPP
#define THW_SORTS_HPP

#include <iostream>
#include <vector>
#include <utility>

std::vector<int> bubbleSort(int len, std::vector<int> arr);
std::vector<int> bubbleIversonOneSort(int len, std::vector<int> arr);
std::vector<int> bubbleIversonOneAndTwoSort(int len, std::vector<int> arr);
std::vector<int> selectionSort(int len, std::vector<int> arr);
std::vector<int> linearInsertionSort(int len, std::vector<int> arr);
std::vector<int> binaryInsertionSort(int len, std::vector<int> arr);
std::vector<int> countingSort(int len, std::vector<int> arr);
std::vector<int> radixSort(int len, std::vector<int> arr);
std::vector<int> mergeSort(int len, std::vector<int> arr);
std::vector<int> hoarSort(int len, std::vector<int> arr);
std::vector<int> lomutoSort(int len, std::vector<int> arr);
std::vector<int> heapSort(int len, std::vector<int> arr);

#endif
