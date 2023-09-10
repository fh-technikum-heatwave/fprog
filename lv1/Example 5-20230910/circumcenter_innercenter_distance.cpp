#include <iostream>
#include <tuple>
 
// Helper function to calculate square root without using std::sqrt()
double square_root_helper(const int i, const int max_iterations, const double epsilon, const double x,
                          const double low, const double high)
{

    double mid = (low + high) / 2.0;
    double mid_square = mid * mid;
    if (i >= max_iterations)
    {
        return mid;
    }

    if (high - low < epsilon)
    {
        return mid;
    }
    else if (mid_square > x)
    {
        return square_root_helper(i + 1, max_iterations, epsilon, x, low, mid);
    }
    else if (mid_square < x)
    {
        return square_root_helper(i + 1, max_iterations, epsilon, x, mid, high);
    }

    return mid;
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
    return square_root_helper(0, max_iterations, epsilon, x, 0, x);
}

std::tuple<double, double, double> calculate_area_and_radii(const double a, const double b, const double c)
{
    double s = (a + b + c) / 2;
    double area = square_root(s * (s - a) * (s - b) * (s - c));
    double inradius = area / s;
    return std::make_tuple(((a * b * c) / (4 * area)), inradius, area);
}

double calculate_distance(const double circumradius, const double inradius)
{
    return square_root(circumradius * circumradius - 2 * circumradius * inradius);
}

int main()
{
    double a = 3, b = 4, c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    auto values = calculate_area_and_radii(a, b, c);
    std::cout << "Inradius: " << std::get<1>(values) << "\n";
    std::cout << "Circumradius: " << std::get<0>(values) << "\n";

    double distance = calculate_distance(std::get<0>(values), std::get<1>(values));
    std::cout << "Distance between circumcenter and incenter: " << distance << "\n";

    return 0;
}
