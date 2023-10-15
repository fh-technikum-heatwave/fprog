#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <optional>

using namespace std;
using namespace std::placeholders;

template <typename T>
struct Maybe
{

    const optional<T> value; // vector

    template <typename U, typename Func>
    Maybe<U> apply(Func operation) const
    {
        if (value)
        {
            return operation(value.value());
        }
        else
        {
            return Maybe<U>{};
        }
    }
};

// Lambda function to read integers from a file
auto readIntegersFromFile = [](const std::string &filename) -> Maybe<std::vector<int>>
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::vector<int> integers;
        int num;
        while (file >> num)
        {
            integers.push_back(num);
        }
        file.close();
        return Maybe<std::vector<int>>{integers};
    }
    else
    {
        return Maybe<std::vector<int>>{std::nullopt};
    }
};

Maybe<std::vector<int>> readFile(const std::string &filename)
{
    return readIntegersFromFile("numbers.txt");
}

// Immutable function to sum integers
auto sumIntegers = [](const std::vector<int> &integers) -> Maybe<int>
{
    int sum = 0;
    for (int num : integers)
    {
        sum += num;
    }
    return Maybe<int>{sum};
};

int main()
{
    auto filename = "numbers.txt";

    auto maybeIntegers = readFile(filename);
    auto maybeSum = Maybe<std::vector<int>>{maybeIntegers.value.value()}.apply<int>(sumIntegers);

    if (maybeSum.value)
    {
        cout << "Sum of integers in file " << filename << " is " << maybeSum.value.value() << endl;
    }
    else
    {
        cout << "Error reading file " << filename << endl;
    }
    return 0;
}
