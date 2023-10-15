#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <optional>

template <typename T>
using Maybe = std::optional<T>;

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
    return Maybe<std::vector<int>>(integers);
  }
  else
  {
    return std::nullopt;
  }
};

// Immutable function to sum integers
auto sumIntegers = [](const std::vector<int> &integers) -> Maybe<int>
{
  int sum = 0;
  for (int num : integers)
  {
    sum += num;
  }
  return sum;
};

int main()
{
  auto filename = "numbers.txt";
  auto result = readIntegersFromFile(filename);

  if (result)
  {
    auto sum = sumIntegers(result.value());
    if (sum)
    {
      std::cout << sum.value() << std::endl;
    }
    else
    {
      std::cout << "Error calculating the sum." << std::endl;
    }
  }
  else
  {
    std::cout << "Error reading the file." << std::endl;
  }

  return 0;
}
