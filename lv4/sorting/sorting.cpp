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

using namespace std;
using namespace std::placeholders;

// extra Methods
auto concatenate = [](const auto &first, const auto &second)
{
    auto result{first};
    result.insert(result.end(), make_move_iterator(second.begin()), make_move_iterator(second.end()));
    return result;
};

auto distributeToBuckets = [](const int &value, const double &range) -> int
{
    return static_cast<int>(value / range);
};

// Task 1
// insertionSort for bucketSort
auto insertionSort = [](const std::vector<int> &input) -> std::vector<int>
{
    std::vector<int> result = input;
    int n = result.size();
    for (int i = 1; i < n; ++i)
    {
        int key = result[i];
        int j = i - 1;
        while (j >= 0 && result[j] > key)
        {
            result[j + 1] = result[j];
            j--;
        }
        result[j + 1] = key;
    }
    return result; // Return the sorted vector
};

auto bucketSort = [](const auto array, const auto k)
{
    // Create k empty buckets
    vector<vector<int>> buckets(k);

    // Find the maximum value in the array
    int max_val = *max_element(array.begin(), array.end());

    // Calculate the range for each bucket
    double range = (max_val + 1) / static_cast<double>(k);

    for (const auto &value : array)
    {
        int bucket_idx = distributeToBuckets(value, range);
        buckets[bucket_idx].push_back(value);
    }

    // Sort each bucket using insertion sort
    for (auto &bucket : buckets)
    {
        bucket = insertionSort(bucket);
    }

    // // Sort each bucket using insertion sort
    // for_each(buckets.begin(), buckets.end(), insertionSortBucket);

    vector<int> result = std::accumulate(buckets.begin(), buckets.end(), vector<int>(), concatenate);

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

// Task 2

void insertSorted(std::vector<int> &arr, int n)
{
    if (n > 0)
    {
        insertSorted(arr, n - 1);
        int x = arr[n];
        int j = n - 1;
        while (j >= 0 && arr[j] > x)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = x;
    }
}

vector<int> insertionSortRecursive(const std::vector<int> &input)
{
    std::vector<int> result = input;
    if (result.size() <= 1)
    {
        return result;
    }
    else
    {
        insertSorted(result, result.size() - 1);
        return result;
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