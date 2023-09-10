#include <iostream>

// Global variables
double a, b, c;
double s, area, circumradius, inradius, distance;

// Helper function to calculate square root without using std::sqrt()
double square_root(double x, double epsilon = 1e-10, int max_iterations = 1000) {
    std::cout << "Calculating square root of " << x << "\n";
    if (x < 0) {
        return -1; // Invalid input
    }
    if (x == 0) {
        return 0;
    }

    double low = 0, high = x;
    double mid;
    for (int i = 0; i < max_iterations; ++i) {
        mid = (low + high) / 2.0;
        double mid_square = mid * mid;

        std::cout << "Iteration: " << i + 1 << ", mid: " << mid << ", mid_square: " << mid_square << "\n";

        if (mid_square > x) {
            high = mid;
        } else if (mid_square < x) {
            low = mid;
        }

        if (high - low < epsilon) {
            break;
        }
    }

    return mid;
}

void calculate_area_and_radii() {
    s = (a + b + c) / 2;
    area = square_root(s * (s - a) * (s - b) * (s - c));
    inradius = area / s;
    circumradius = (a * b * c) / (4 * area);
}

void calculate_distance() {
    distance = square_root(circumradius * circumradius - 2 * circumradius * inradius);
}

int main() {
    a = 3, b = 4, c = 5;
    std::cout << "Triangle sides: a = " << a << ", b = " << b << ", c = " << c << "\n";

    calculate_area_and_radii();
    std::cout << "Inradius: " << inradius << "\n";
    std::cout << "Circumradius: " << circumradius << "\n";

    calculate_distance();
    std::cout << "Distance between circumcenter and incenter: " << distance << "\n";

    return 0;
}
