#include <iostream>
#include <fstream>
#include <ctime>
#include "sorts/sorts.hpp"

typedef std::vector<int> (*Func)(int len, std::vector<int> arr);

constexpr int numOfFuncs = 12;
constexpr int arrLength = 1000;

double randomArrayMeasure(Func func) {
    clock_t start;
    clock_t end;
    // TODO...
    return static_cast<double>(start - end) * 1000 / CLOCKS_PER_SEC;
}

double sortedArrayMeasure(Func func) {
    clock_t start;
    clock_t end;
    // TODO...
    return static_cast<double>(start - end) * 1000 / CLOCKS_PER_SEC;
}

double reverseSortedArrayMeasure(Func func) {
    clock_t start;
    clock_t end;
    // TODO...
    return static_cast<double>(start - end) * 1000 / CLOCKS_PER_SEC;
}

double allElementsAreSameArrayMeasure(Func func) {
    clock_t start;
    clock_t end;
    // TODO...
    return static_cast<double>(start - end) * 1000 / CLOCKS_PER_SEC;
}

void measure(Func func, std::string const &func_name) {
    std::ofstream fout("../docs/results.txt");

    fout << func_name << ' ' << "benchmark:";
    fout << "    " << "1). Random array:" << randomArrayMeasure(func);
    fout << "    " << "2). Sorted array:" << sortedArrayMeasure(func);
    fout << "    " << "3). Reverse sorted array:" << reverseSortedArrayMeasure(func);
    fout << "    " << "4). Array with all same elements:" << allElementsAreSameArrayMeasure(func);

    fout.close();
}

int main() {
    std::cout << "Start" << '\n';

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
        measure(funcs[i], func_names[i]);
    }

    std::cout << "End" << '\n';
    return 0;
}
