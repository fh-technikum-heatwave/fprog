#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <optional>

// Lambda function to read integers from a file
auto readIntegersFromFile = [](const std::string &filename) -> std::optional<std::vector<int>>
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
    return integers;
  }
  else
  {
    return std::nullopt;
  }
};

// Immutable function to sum integers
auto sumIntegers = [](const std::vector<int> &integers) -> std::optional<int>
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
