#include <iostream>
#include <tuple>

// Helper function to calculate square root without using std::sqrt()
auto square_root = [](double x)
{
    return [x](double epsilon = 1e-10, int max_iterations = 1000) -> double
    {
        if (x < 0)
        {
            return -1; // Invalid input
        }
        if (x == 0)
        {
            return 0;
        }

        double low = 0, high = x;
        double mid;
        for (int i = 0; i < max_iterations; ++i)
        {
            mid = (low + high) / 2.0;
            double mid_square = mid * mid;

            if (mid_square > x)
            {
                high = mid;
            }
            else if (mid_square < x)
            {
                low = mid;
            }

            if (high - low < epsilon)
            {
                break;
            }
        }

        return mid;
    };
};
auto calculate_area_and_radii = [](double a)
{
    return [a](double b)
    {
        return [a, b](double c) -> std::tuple<double, double, double>
        {
            double s = (a + b + c) / 2;
            double area = square_root(s * (s - a) * (s - b) * (s - c))();
            double inradius = area / s;
            double circumradius = (a * b * c) / (4 * area);
            return std::make_tuple(((a * b * c) / (4 * area)), inradius, area);
        };
    };
};

// double circumradius, inradius
auto calculate_distance = [](double circumradius)
{
    return [circumradius](double inradius) -> double
    {
        return square_root(circumradius * circumradius - 2 * circumradius * inradius)();
    };
};

int main()
{
    double a = 3, b = 4, c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    auto triple = calculate_area_and_radii(a)(b)(c);

    std::cout << "Inradius: " << std::get<1>(triple) << "\n";
    std::cout << "Circumradius: " << std::get<0>(triple) << "\n";

    std::cout << "Distance between circumcenter and incenter: " << calculate_distance(std::get<0>(triple))(std::get<1>(triple)) << "\n";

    return 0;
}
