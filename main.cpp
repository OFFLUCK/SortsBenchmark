#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <ctime>
#include "sorts/sorts.hpp"

typedef std::vector<int> (*Func)(int len, std::vector<int> arr);

constexpr int numOfFuncs = 12;
constexpr int arrLength = 1000;

double randomArrayMeasure(Func func) {
    std::vector<int> arr(arrLength);
    for (int i = 0; i < arrLength; ++i) {
        arr[i] = i;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(arr.begin(), arr.end(), gen);

    clock_t start = clock();
    func(arrLength, arr);
    clock_t end = clock();

    return static_cast<double>(end - start) * 1000 / CLOCKS_PER_SEC;
}

double sortedArrayMeasure(Func func) {
    std::vector<int> arr(arrLength);
    for (int i = 0; i < arrLength; ++i) {
        arr[i] = i;
    }

    clock_t start = clock();
    func(arrLength, arr);
    clock_t end = clock();

    return static_cast<double>(end - start) * 1000 / CLOCKS_PER_SEC;
}

double reverseSortedArrayMeasure(Func func) {
    std::vector<int> arr(arrLength);
    for (int i = 0; i < arrLength; ++i) {
        arr[i] = arrLength - i - 1;
    }

    clock_t start = clock();
    func(arrLength, arr);
    clock_t end = clock();

    return static_cast<double>(end - start) * 1000 / CLOCKS_PER_SEC;
}

double allElementsAreSameArrayMeasure(Func func) {
    std::vector<int> arr(arrLength, arrLength);

    clock_t start = clock();
    func(arrLength, arr);
    clock_t end = clock();

    return static_cast<double>(end - start) * 1000 / CLOCKS_PER_SEC;
}

void measure(Func func, std::string const &func_name, std::ofstream &fout) {
    fout << func_name << ' ' << "benchmark:" << '\n';
    fout << "    " << "1). Random array: " << randomArrayMeasure(func) << "ms" << '\n';
    fout << "    " << "2). Sorted array: " << sortedArrayMeasure(func) << "ms" << '\n';
    fout << "    " << "3). Reverse sorted array: " << reverseSortedArrayMeasure(func) << "ms" << '\n';
    fout << "    " << "4). Array with all same elements: " << allElementsAreSameArrayMeasure(func) << "ms" << '\n';
}

void printSeparator(std::ofstream &fout) {
    fout << '\n';
    for (int i = 0; i < 100; ++i) {
        fout << '-';
    }
    fout << '\n';
}

int main() {
    std::cout << "Start" << '\n';
    std::ofstream fout("../docs/results.txt");

    std::vector<std::string> func_names = {
            "Bubble sort",
            "Bubble sort Iverson 1",
            "Bubble sort Iverson 1 & 2",
            "Selection sort",
            "Linear insertion sort",
            "Binary insertion sort",
            "Counting sort",
            "Radix sort",
            "Merge sort",
            "Hoar sort",
            "Lomuto sort",
            "Heap sort",
    };

    std::vector<Func> funcs = {
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

    for (int i = 0; i < numOfFuncs; ++i) {
        std::cout << "Measuring" << ' ' << func_names[i] << '\n';
        measure(funcs[i], func_names[i], fout);
        printSeparator(fout);
    }

    std::cout << "End" << '\n';
    return 0;
}
