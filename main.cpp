#include <iostream>
#include <fstream>
#include "sorts/sorts.hpp"

constexpr int numOfFuncs = 12;
typedef std::vector<int> (*func)(int len, std::vector<int> arr);

int main() {
    std::cout << "test" << '\n';
    std::ifstream fin;
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

    std::vector<func> funcs = {
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

    double time = 0;
    for (int i = 0; i < numOfFuncs; ++i) {
        // TODO: time measurement.
        fout << func_names[i] << ": " << time << "ms" << '\n';
    }

    return 0;
}
