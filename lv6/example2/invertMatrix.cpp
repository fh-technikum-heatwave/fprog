#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <tuple>
#include <string>
#include <optional>

using errorMessage = std::optional<std::string>;
using Matrix = std::vector<std::vector<double>>;


// Define a Result type using a tuple
template <typename T>
using Result = std::tuple<bool, T, errorMessage>;

template <typename T>
Result<T> Just(T value)
{
    return std::make_tuple(true, value, std::nullopt);
}

template <typename T>
Result<T> Nothing(std::string errorMessage)
{
    return std::make_tuple(false, T(), std::optional<std::string>(errorMessage));
}



// Immutable function to calculate the determinant of a 2x2 matrix
auto determinant = [](const Matrix &mat) -> Result<double>
{
    if (mat.size() == 2 && mat[0].size() == 2 && mat[1].size() == 2)
    {
        return Just(mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]);
    }
    return Nothing<double>("Matrix is not invertible"); // Return Nothing to indicate the matrix is not invertible
};

// Immutable function to attempt matrix inversion
auto invert_matrix = [](const Matrix &mat) -> Result<Matrix>
{
    Result<double> det = determinant(mat);
    if (std::get<0>(det))
    {
        double determinantValue = std::get<1>(det);
        if (determinantValue == 0)
        {
            return Nothing<Matrix>("Matrix is not invertible"); // Return Nothing to indicate an error
        }
        Matrix inverted(2, std::vector<double>(2, 0.0));
        inverted[0][0] = mat[1][1] / determinantValue;
        inverted[0][1] = -mat[0][1] / determinantValue;
        inverted[1][0] = -mat[1][0] / determinantValue;
        inverted[1][1] = mat[0][0] / determinantValue;
        return Just(inverted);
    }
    return Nothing<Matrix>(std::get<2>(det).value_or("Unknown error")); // Return Nothing with the error message
};

int main()
{
    // Sample matrix
    Matrix sampleMatrix = {{4, 7}, {2, 6}};

    // Attempt to invert the matrix
    Result<Matrix> result = invert_matrix(sampleMatrix);

    if (std::get<0>(result))
    {
        std::cout << "Inverted Matrix:\n";
        const Matrix &inverted = std::get<1>(result);
        for (const auto &row : inverted)
        {
            for (const double val : row)
            {
                std::cout << val << " ";
            }
            std::cout << '\n';
        }
    }
    else
    {
        std::cout << "Error: " << std::get<2>(result).value_or("Unknown error") << '\n';
    }

    return 0;
}
