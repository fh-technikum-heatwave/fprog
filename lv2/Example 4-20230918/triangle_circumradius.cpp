#include <iostream>

// Helper function to calculate square root without using std::sqrt()
auto square_root = [](double x)
{
    return [x](double epsilon = 1e-10, int max_iterations = 1000) ->double
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

// double a, b, c
auto calculate_circumradius = [](double a)
{
    return [a](double b)
    {
        return [a, b](double c) -> double
        {
            double s = (a + b + c) / 2;
            double area = square_root(s * (s - a) * (s - b) * (s - c))();
            return (a * b * c) / (4 * area);
        };
    };
};

int main()
{
    double a = 3, b = 4, c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";
    std::cout << "Circumradius: " <<  calculate_circumradius(a)(b)(c) << "\n";

    return 0;
}
