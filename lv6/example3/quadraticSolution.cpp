#include <iostream>
#include <cmath>
#include <optional>
#include <complex>

// Define a simple QuadraticSolution struct to represent the solutions.
struct QuadraticSolution {
    std::optional<double> real_root1;
    std::optional<double> real_root2;
    // std::optional<std::complex<double>> complex_root;
};

// Immutable function to solve the quadratic equation and return an std::optional<QuadraticSolution>.
auto solve_quadratic = [](double a, double b, double c) -> std::optional<QuadraticSolution> {
    double discriminant = b * b - 4 * a * c;
    
    if (discriminant > 0) {
        double sqrt_discriminant = std::sqrt(discriminant);
        double root1 = (-b + sqrt_discriminant) / (2 * a);
        double root2 = (-b - sqrt_discriminant) / (2 * a);
        return QuadraticSolution{root1, root2};
    } else if (discriminant == 0) {
        double root = -b / (2 * a);
        return QuadraticSolution{root, std::nullopt};
    } else {
        // std::complex<double> complex_root1(-b / (2 * a), std::sqrt(-discriminant) / (2 * a));
        // std::complex<double> complex_root2(-b / (2 * a), -std::sqrt(-discriminant) / (2 * a));
        // return QuadraticSolution{std::nullopt, std::nullopt, complex_root1};

        return std::nullopt;
    }
};

int main() {

    // std::optional<QuadraticSolution> result = solve_quadratic(3,2,1); // no real root
    std::optional<QuadraticSolution> result = solve_quadratic(1,2,1); // one real roots
    // std::optional<QuadraticSolution> result = solve_quadratic(5,7,3); // 2 real numbers

    if (result.has_value()) {
        QuadraticSolution solution = result.value();
        if (solution.real_root1.has_value() && solution.real_root2.has_value()) {
            std::cout << "Real Roots: " << solution.real_root1.value() << " and " << solution.real_root2.value() << '\n';
        } else if (solution.real_root1.has_value()) {
            std::cout << "Real Root: " << solution.real_root1.value() << '\n';
        } else {
            // std::cout << "Complex Roots:" << solution.complex_root.value() << '\n';
            std::cout << "Complex Roots:" << '\n';
        }
    } else {
        std::cout << "No real roots. Equation is complex." << '\n';
    }

    return 0;
}
