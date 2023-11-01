#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "functional"
#include <list>
#include <numeric>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <optional>
#include <algorithm>
#include <cmath>
#include <functional>
#include <ranges> // Include the Ranges library

using namespace std;
using namespace std::placeholders;

// namespace sr = std::ranges

// extra Methodsfunctional
auto concatenate = [](const auto &first, const auto &second)
{
    auto result{first};
    result.insert(result.end(), make_move_iterator(second.begin()), make_move_iterator(second.end()));
    return result;
};

auto distributeToBuckets = [](int value, double range)
{
    return static_cast<int>(value / range);
};

auto bucketSort = [](const std::vector<int> &input, int numBuckets)
{
    if (input.empty() || numBuckets <= 0)
    {
        return std::vector<int>{};
    }

    int max_val = *std::ranges::max_element(input);
    double range = (max_val + 1.0) / static_cast<double>(numBuckets);

    std::vector<std::vector<int>> buckets(numBuckets);

    for (int value : input)
    {
        int bucket_idx = distributeToBuckets(value, range);
        buckets[bucket_idx].push_back(value);
    }

    auto sortedBuckets = buckets | std::ranges::views::transform([](auto &bucket) -> std::vector<int>
                                                                 {
    std::ranges::sort(bucket);
    return bucket; });

    auto combinedBuckets = std::ranges::views::transform(sortedBuckets, [](const auto &bucket) -> std::vector<int>
                                                         { return bucket; });
    std::vector<int> result;
    for (const auto &bucket : combinedBuckets)
    {
        result.insert(result.end(), bucket.begin(), bucket.end());
    }

    return result;
};

TEST_CASE("Bucket Sort")
{
    vector<int> input{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
    CHECK_EQ(bucketSort(input, 3), expected);
}

TEST_CASE("Bucket Sort")
{
    vector<int> input{6, 7, 8, 9, 1, 2, 3, 4, 5};
    vector<int> input2{9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
    CHECK_EQ(bucketSort(input, 3), expected);
    CHECK_EQ(bucketSort(input2, 3), expected);
}

TEST_CASE("Bucket Sort - not changing input Value")
{
    vector<int> input{6, 7, 8, 9, 1, 2, 3, 4, 5};
    vector<int> expected{6, 7, 8, 9, 1, 2, 3, 4, 5};
    bucketSort(input, 3);
    CHECK_EQ(input, expected);
}

// Task 2

std::vector<int> insertionSortRecursive(const std::vector<int> &input)
{
    // Define a lambda function to insert an element into a sorted vector
    auto insertSorted = [](const std::vector<int> sorted, int value)
    {
        std::vector<int> result = sorted;
        auto it = std::upper_bound(result.begin(), result.end(), value);
        result.insert(it, value);
        return result;
    };

    if (input.size() <= 1)
    {
        return input;
    }
    else
    {
        // Recursively sort the subvector from index 1 to the end
        std::vector<int> tail = insertionSortRecursive(std::vector<int>(input.begin() + 1, input.end()));

        // Insert the first element into the sorted tail
        int firstElement = input[0];
        return insertSorted(tail, firstElement);
    }
}

TEST_CASE("Insertion Sort")
{
    vector<int> input{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
    CHECK_EQ(insertionSortRecursive(input), expected);
}

TEST_CASE("Insertion Sort")
{
    vector<int> input{6, 7, 8, 9, 1, 2, 3, 4, 5};
    vector<int> input2{9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
    CHECK_EQ(insertionSortRecursive(input), expected);
    CHECK_EQ(insertionSortRecursive(input2), expected);
}

TEST_CASE("Insertion Sort - not changing input Value")
{
    vector<int> input{6, 7, 8, 9, 1, 2, 3, 4, 5};
    vector<int> expected{6, 7, 8, 9, 1, 2, 3, 4, 5};
    insertionSortRecursive(input);
    CHECK_EQ(input, expected);
}

// Task 3
template <typename T>
std::vector<T> bubbleSort(const std::vector<T> list)
{
    std::vector<T> sortedArray = list;
    bool swapped;

    do
    {
        swapped = false;

        for (size_t i = 1; i < sortedArray.size(); i++)
        {
            if (sortedArray[i - 1] > sortedArray[i])
            {
                std::swap(sortedArray[i - 1], sortedArray[i]);
                swapped = true;
            }
        }
    } while (swapped);

    return sortedArray;
}

TEST_CASE("Bubble Sort")
{
    vector<int> input{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
    CHECK_EQ(bubbleSort(input), expected);
}

TEST_CASE("Bubble Sort")
{
    vector<int> input{6, 7, 8, 9, 1, 2, 3, 4, 5};
    vector<int> input2{9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
    CHECK_EQ(bubbleSort(input), expected);
    CHECK_EQ(bubbleSort(input2), expected);
}

TEST_CASE("Bubble Sort - not changing input Value")
{
    vector<int> input{6, 7, 8, 9, 1, 2, 3, 4, 5};
    vector<int> expected{6, 7, 8, 9, 1, 2, 3, 4, 5};
    bubbleSort(input);
    CHECK_EQ(input, expected);
}

// Task 4
auto selectionSort = [](const std::vector<int> inputArray) -> std::vector<int>
{
    std::vector<int> sortedArray = inputArray;

    for (size_t i = 0; i < sortedArray.size() - 1; i++)
    {
        size_t jMin = i;

        for (size_t j = i + 1; j < sortedArray.size(); j++)
        {
            if (sortedArray[j] < sortedArray[jMin])
            {
                jMin = j;
            }
        }

        if (jMin != i)
        {
            std::swap(sortedArray[i], sortedArray[jMin]);
        }
    }

    return sortedArray;
};

TEST_CASE("Selection Sort")
{
    vector<int> input{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
    CHECK_EQ(selectionSort(input), expected);
}

TEST_CASE("Selection Sort")
{
    vector<int> input{6, 7, 8, 9, 1, 2, 3, 4, 5};
    vector<int> input2{9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
    CHECK_EQ(selectionSort(input), expected);
    CHECK_EQ(selectionSort(input2), expected);
}

TEST_CASE("Selection Sort - not changing input Value")
{
    vector<int> input{6, 7, 8, 9, 1, 2, 3, 4, 5};
    vector<int> expected{6, 7, 8, 9, 1, 2, 3, 4, 5};
    selectionSort(input);
    CHECK_EQ(input, expected);
}

// Task 5

std::function<std::vector<int>(std::vector<int>)> quicksort = [](const std::vector<int> inputArray) -> std::vector<int>
{
    if (inputArray.size() <= 1)
    {
        return inputArray;
    }

    int pivotIndex = inputArray.size() / 2;
    int pivot = inputArray[pivotIndex];

    std::vector<int> left;
    std::vector<int> right;

    for (size_t i = 0; i < inputArray.size(); i++)
    {
        if (static_cast< int>(i) == pivotIndex)
        {
            continue;
        }
        if (inputArray[i] <= pivot)
        {
            left.push_back(inputArray[i]);
        }
        else
        {
            right.push_back(inputArray[i]);
        }
    }

    // Use recursion to sort left and right partitions
    std::vector<int> sortedLeft = quicksort(left);
    std::vector<int> sortedRight = quicksort(right);

    // Combine sorted partitions with pivot
    std::vector<int> sortedArray;
    sortedArray.reserve(sortedLeft.size() + 1 + sortedRight.size());
    sortedArray.insert(sortedArray.end(), sortedLeft.begin(), sortedLeft.end());
    sortedArray.push_back(pivot);
    sortedArray.insert(sortedArray.end(), sortedRight.begin(), sortedRight.end());

    return sortedArray;
};

TEST_CASE("Quick Sort")
{
    vector<int> input{1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
    CHECK_EQ(quicksort(input), expected);
}

TEST_CASE("Quick Sort")
{
    vector<int> input{6, 7, 8, 9, 1, 2, 3, 4, 5};
    vector<int> input2{9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9};
    CHECK_EQ(quicksort(input), expected);
    CHECK_EQ(quicksort(input2), expected);
}

TEST_CASE("Quick Sort - not changing input Value")
{
    vector<int> input{6, 7, 8, 9, 1, 2, 3, 4, 5};
    vector<int> expected{6, 7, 8, 9, 1, 2, 3, 4, 5};
    quicksort(input);
    CHECK_EQ(input, expected);
}
