#include <iostream>
#include <functional>
#include <optional>
#include <numeric>
#include <iostream>
#include <list>
#include <map>
#include <string>

template <typename ValueType>
struct Maybe
{
    typedef std::function<std::optional<ValueType>(const ValueType, const ValueType)> OperationType;
    const std::optional<ValueType> value;

    std::optional<ValueType> apply(const OperationType operation, const std::optional<ValueType> second) const
    {
        if (value == std::nullopt || second == std::nullopt)
            return std::nullopt;
        return operation(value.value(), second.value());
    }
};

// Lambda function for integer division

auto divide = [](int first, int second) -> std::optional<int>
{
    return (second == 0) ? std::nullopt : std::make_optional(first / second);
};

// Lambda function to print the result
auto printResult = [](auto result)
{
    if (result.has_value())
    {
        std::cout << "Result: " << result.value() << std::endl;
    }
    else
    {
        std::cout << "Error: Division by zero or invalid input." << std::endl;
    }
};

int main()
{

    auto result = Maybe<int>{5}.apply(divide, 2);

    printResult(result);

    return 0;
}
