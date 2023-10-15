#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <tuple>
#include <string>
#include <optional>

using Matrix = std::vector<std::vector<double>>;

template <typename T>
struct Result
{
    bool valid;
    T value;
    std::string errorMessage;

    static Result Just(T value)
    {
        return {true, value, ""};
    }

    static Result Nothing(std::string errorMessage)
    {
        return {false, T(), errorMessage};
    }

    template <typename U, typename Func>
    auto apply(Func func) -> Result<U>
    {
        if (valid)
        {
            return func(value);
        }
        return Result<U>::Nothing(errorMessage);
    }
};

// Immutable function to calculate the determinant of a 2x2 matrix
auto determinant = [](const Matrix &mat) -> Result<double>
{
    if (mat.size() == 2 && mat[0].size() == 2 && mat[1].size() == 2)
    {
        return Result<double>::Just(mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]);
    }
    return Result<double>::Nothing("Matrix is not invertible"); // Return Nothing to indicate the matrix is not invertible
};

// Immutable function to attempt matrix inversion
auto invert_matrix = [](const Matrix &mat) -> Result<Matrix>
{
    return determinant(mat).apply<Matrix>([mat](double determinantValue) -> Result<Matrix>
                                          {
        if (determinantValue == 0)
        {
            return Result<Matrix>::Nothing("Matrix is not invertible"); // Return Nothing to indicate an error
        }
        Matrix inverted(2, std::vector<double>(2, 0.0));
        inverted[0][0] = mat[1][1] / determinantValue;
        inverted[0][1] = -mat[0][1] / determinantValue;
        inverted[1][0] = -mat[1][0] / determinantValue;
        inverted[1][1] = mat[0][0] / determinantValue;
        return Result<Matrix>::Just(inverted); });

    // Return Nothing with the error message
};

int main()
{
    // Sample matrix
    Matrix sampleMatrix = {{2, 1}, {4, 2}}; // Case for not valid matrix
                                            //   Matrix sampleMatrix = {{4, 7}, {2,6}};//

    // Attempt to invert the matrix
    Result<Matrix> result = invert_matrix(sampleMatrix);

    if (result.valid)
    {
        std::cout << "Inverted Matrix:\n";
        const Matrix &inverted = result.value;
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
        std::cout << "Error: " << result.errorMessage << '\n';
    }

    return 0;
}
