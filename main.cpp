#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <ctime>
#include "sorts/sorts.hpp"

typedef std::pair<std::vector<int>, uint64_t> (*Func)(size_t len, std::vector<int> arr);

constexpr int numOfFuncs = 12;
constexpr int milis = 1000;
constexpr int sortAttempts = 100;
constexpr int arrLength = 1000;

std::vector<int> random_array(arrLength);
void initRandomArray()
{
    for (int i = 0; i < arrLength; ++i)
    {
        random_array[i] = i;
    }
}
void updateRandomArray()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(random_array.begin(), random_array.end(), gen);
}

void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<double>>> dataset)
{
    std::ofstream myFile(filename);
    for (int j = 0; j < dataset.size(); ++j)
    {
        myFile << dataset.at(j).first;
        if (j != dataset.size() - 1)
            myFile << ";";
    }
    myFile << "\n";
    for (int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for (int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if (j != dataset.size() - 1)
                myFile << ";";
        }
        myFile << "\n";
    }
    myFile.close();
}

/**
 * @brief Тест на ранд. наборе
 *
 * @param func
 * @return std::pair<double, uint64_t> <time, el operations>
 */
std::pair<double, uint64_t> randomArrayMeasure(Func func)
{
    std::vector<int> arr(arrLength);
    for (int i = 0; i < arrLength; ++i)
    {
        arr[i] = random_array[i];
    }
    clock_t start = clock();
    auto sortRes = func(arrLength, arr);
    clock_t end = clock();

    return std::make_pair(static_cast<double>(end - start) * milis / CLOCKS_PER_SEC, sortRes.second);
}

std::pair<double, uint64_t> sortedArrayMeasure(Func func)
{
    std::vector<int> arr(arrLength);
    for (int i = 0; i < arrLength; ++i)
    {
        arr[i] = i;
    }

    clock_t start = clock();
    auto sortRes = func(arrLength, arr);
    clock_t end = clock();

    return std::make_pair(static_cast<double>(end - start) * milis / CLOCKS_PER_SEC, sortRes.second);
}

std::pair<double, uint64_t> reverseSortedArrayMeasure(Func func)
{
    std::vector<int> arr(arrLength);
    for (int i = 0; i < arrLength; ++i)
    {
        arr[i] = arrLength - i - 1;
    }

    clock_t start = clock();
    auto sortRes = func(arrLength, arr);
    clock_t end = clock();

    return std::make_pair(static_cast<double>(end - start) * milis / CLOCKS_PER_SEC, sortRes.second);
}

std::pair<double, uint64_t> allElementsAreSameArrayMeasure(Func func)
{
    std::vector<int> arr(arrLength, arrLength);

    clock_t start = clock();
    auto sortRes = func(arrLength, arr);
    clock_t end = clock();

    return std::make_pair(static_cast<double>(end - start) * milis / CLOCKS_PER_SEC, sortRes.second);
}

std::vector<double> sort_name_vector;
std::pair<std::vector<double>, std::vector<double>> rnd_test;
std::pair<std::vector<double>, std::vector<double>> sorted_test;
std::pair<std::vector<double>, std::vector<double>> reversed_test;
std::pair<std::vector<double>, std::vector<double>> const_el_test;

void measure(Func func, int func_ind, std::ofstream &fout)
{
    sort_name_vector.push_back(func_ind);
    auto res = randomArrayMeasure(func);
    rnd_test.first.push_back(res.first);
    rnd_test.second.push_back(res.second);
    auto res2 = sortedArrayMeasure(func);
    sorted_test.first.push_back(res2.first);
    sorted_test.second.push_back(res2.second);
    auto res3 = reverseSortedArrayMeasure(func);
    reversed_test.first.push_back(res3.first);
    reversed_test.second.push_back(res3.second);
    auto res4 = allElementsAreSameArrayMeasure(func);
    const_el_test.first.push_back(res4.first);
    const_el_test.second.push_back(res4.second);
}

void saveResults()
{
    std::vector<std::pair<std::string, std::vector<double>>> vals = {
        {"SORT_NAME", sort_name_vector},
        {"RND_TIME", rnd_test.first},
        {"RND_STEPS", rnd_test.second},
        {"SORTED_TIME", sorted_test.first},
        {"SORTED_STEPS", sorted_test.second},
        {"REVERSED_TIME", reversed_test.first},
        {"REVERSED_STEPS", reversed_test.second},
        {"SAME_EL_TIME", const_el_test.first},
        {"SAME_EL_STEPS", const_el_test.second},
    };
    write_csv("../docs/res.csv", vals);
}

void printSeparator(std::ofstream &fout)
{
    fout << '\n';
    for (int i = 0; i < 100; ++i)
    {
        fout << '-';
    }
    fout << '\n';
}

int main()
{
    std::cout << "Start" << '\n';
    std::ofstream fout("../docs/results.txt");

    // std::vector<std::string> func_names = {
    //     "Bubble sort",
    //     "Bubble sort Iverson 1",
    //     "Bubble sort Iverson 1 & 2",
    //     "Selection sort",
    //     "Linear insertion sort",
    //     "Binary insertion sort",
    //     "Counting sort",
    //     "Radix sort",
    //     "Merge sort",
    //     "Hoar sort",
    //     "Lomuto sort",
    //     "Heap sort",
    // };

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
    for (size_t j = 0; j < sortAttempts; j++)
    {
        updateRandomArray();
        for (int i = 0; i < numOfFuncs; ++i)
        {
            // std::cout << "Measuring" << ' ' << func_names[i] << '\n';
            measure(funcs[i], i, fout);
            printSeparator(fout);
        }
    }

    saveResults();
    std::cout << "End" << '\n';
    return 0;
}
