#include <iostream>
#include <list>
#include <map>
#include <string>
#include <functional>
#include <numeric>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "doctest.h"
using namespace std;

using namespace std;
using namespace std::placeholders;

auto double_it = bind(multiplies<double>(), _1, 2);
auto decrement = std::bind(std::minus<int>(), _1, 1);

TEST_CASE("Double it")
{
    CHECK_EQ(4, double_it(2));
}

TEST_CASE("Double it")
{
    CHECK_EQ(12, double_it(6));
}

TEST_CASE("Decrement")
{

    // Test the decrement lambda
    CHECK(decrement(5) == 4);
    CHECK(decrement(10) == 9);
    CHECK(decrement(7) == 6);
    CHECK_EQ(1, decrement(2));
    CHECK_EQ(2, decrement(3));
}

auto nonprime_sum = [](const std::vector<int> &numbers)
{
    auto is_prime = [](int num)
    {
        if (num < 2)
            return false;
        for (int i = 2; i * i <= num; ++i)
        {
            if (num % i == 0)
                return false;
        }
        return true;
    };

    int sum = 0;

    for (int num : numbers)
    {
        if (is_prime(num) == false)
        {
            sum += num;
        }
    }

    return sum;
};

TEST_CASE("summing up only nonprime numbers")
{
    std::vector<int> data {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,113};

    CHECK_EQ(113,nonprime_sum(data));
}

TEST_CASE("summing up only nonprime numbers")
{
    std::vector<int> data {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,123};

    CHECK_EQ(236,nonprime_sum(data));
}


auto area = [](const float width, const float height) {
    return abs(width * height);
};

auto circumference = [](const float width, const float height) {
    return abs(2 * (width + height));
};

auto diagonal = [](const float width, const float height) {
    return sqrt(pow(width, 2) + pow(height, 2));
};

auto initialize = [] (const auto width, const auto height) -> map<string, function<int()>>{
return {
	{"area", bind(area, width, height)},
	{"circumference", bind(circumference, width, height)},
	{"diagonal", bind(diagonal, width, height)}
	};
};

TEST_CASE ("Rectangle")
{
  auto rectangle = initialize(3, 4);
  CHECK_EQ(12, rectangle["area"]());
  CHECK_EQ(14, rectangle["circumference"]());
  CHECK_EQ(5, rectangle["diagonal"]());
  
}


auto initialize2 = [] (const auto width, const auto height) -> map<string, function<int()>>{
return {
	{"area", bind(area, width, height)},
	{"circumference", bind(circumference, width, height)},
	{"diagonal", bind(diagonal, width, height)}
	};
};

TEST_CASE ("Rectangle")
{
  auto rectangle = initialize2(3.5, 4.5);
  CHECK_EQ(15, rectangle["area"]());
  CHECK_EQ(16, rectangle["circumference"]());
  CHECK_EQ(5, rectangle["diagonal"]());
  
}


int counter(int previous_count, char c)
{
    return (c == '\n') ? previous_count + 1
                      : previous_count;
}

int count_lines(const std::string &s)
{
    return std::accumulate(
        s.cbegin(), s.cend(),
        0, // Start the count at 0, since there are no lines initially.
        counter
    );
}
TEST_CASE ("Stringtest")
{
 CHECK_EQ(2, count_lines("The quick brown fox\n"
                             "jumps over the lazy do\n"
                             ));
}

TEST_CASE ("Stringtest")
{
 CHECK_EQ(3, count_lines("an ancient pond \n"
                             "a frog jumps in \n"
                             "the splash of water\n"));
}