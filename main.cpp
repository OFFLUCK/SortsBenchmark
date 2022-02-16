#include <iostream>
#include <fstream>
#include <ctime>
#include "sorts/sorts.hpp"

typedef std::vector<int> (*func)(int len, std::vector<int> arr);
constexpr int numOfFuncs = 12;

int main() {
    std::cout << "Start" << '\n';
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

    clock_t start;
    clock_t end;
    double time;
    for (int i = 0; i < numOfFuncs; ++i) {
        std::cout << "Measuring" << ' ' << func_names[i] << '\n';
        start = std::clock();
        // TODO: time measurement.
        end = std::clock();

        time = static_cast<double>(end - start) * 1000 / CLOCKS_PER_SEC;
        fout << func_names[i] << ": " << time << "ms" << '\n';
    }

    std::cout << "End" << '\n';
    return 0;
}
