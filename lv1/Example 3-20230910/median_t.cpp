#include <iostream>

double silly_square_helper(const double x, const double currentValue, const int i)
{
    if (i < x)
    {
        return silly_square_helper(x, currentValue + x, i + 1);
    }

    return currentValue;
}
// Silly square function that is not immutable and not pure
double silly_square(const double x)
{
    // std::cout << "Calculating the silly square of " << x << "\n";
    // double result = 0;
    // for (int i = 0; i < x; ++i)
    // {
    //     result += x;
    //     std::cout << "Iteration " << i + 1 << ": Current result = " << result << "\n";
    // }
    return silly_square_helper(x, x, 1);
}

double square_root_helper(const int i, const int max_iterations, const double epsilon, const double x,
                          const double low, const double high)
{
    if (i < max_iterations)
    {
        double mid = (low + high) / 2.0;
        double mid_square = mid * mid;

        if (mid_square > x)
        {
            return square_root_helper(i + 1, max_iterations, epsilon, x, low, mid);
        }
        else if (mid_square < x)
        {
            return square_root_helper(i + 1, max_iterations, epsilon, x, mid, high);
        }

        if (high - low < epsilon)
        {
            return mid;
        }
    }

    return high;
}

// Helper function to calculate square root without using std::sqrt()
double square_root(const double x, const double epsilon = 1e-10, const int max_iterations = 1000)
{
    // std::cout << "Calculating the square root of " << x << "\n";
    if (x < 0)
    {
        return -1; // Invalid input
    }
    if (x == 0)
    {
        return 0;
    }

    // double low = 0, high = x;
    // double mid;
    // for (int i = 0; i < max_iterations; ++i)
    // {
    //     mid = (low + high) / 2.0;
    //     double mid_square = mid * mid;
    //     // std::cout << "Iteration " << i + 1 << ": Midpoint = " << mid << ", Midpoint squared = " << mid_square << "\n";

    //     if (mid_square > x)
    //     {
    //         high = mid;
    //     }
    //     else if (mid_square < x)
    //     {
    //         low = mid;
    //     }

    //     if (high - low < epsilon)
    //     {
    //         break;
    //     }
    // }

    return square_root_helper(0, max_iterations, epsilon, x, 0, x);
    

    // return mid;
}

double calculate_median(const double a, const double b, const double c)
{
    // std::cout << "Calculating the median of a triangle with sides a = " << a << ", b = " << b << ", c = " << c << "\n";
    return 0.5 * square_root(2 * silly_square(b) + 2 * silly_square(c) - silly_square(a));
}

int main()
{
    double a = 3;
    double b = 4;
    double c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    double median_a = calculate_median(a, b, c);
    a = 4, b = 3, c = 5;
    double median_b = calculate_median(a, b, c);
    a = 5, b = 3, c = 4;
    double median_c = calculate_median(a, b, c);

    std::cout << "Medians:\n";
    std::cout << "Median from vertex A: " << median_a << "\n";
    std::cout << "Median from vertex B: " << median_b << "\n";
    std::cout << "Median from vertex C: " << median_c << "\n";

    return 0;
}
