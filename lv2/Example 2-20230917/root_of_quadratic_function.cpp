#include <iostream>
#include <utility>
#include <complex>

typedef std::complex<double> complex;

auto square = [](double e) -> double
{
  double dummy = e;
  double dummy2 = e;
  for (int i = 1; i < dummy2; i++)
  {
    e = e + dummy;
    // std::cout << "i: " << i << " dummy:" << dummy << " e:" << e << std::endl;
  }
  // std::cout << "square:" << e << std::endl;
  return e;
};

inline auto squareroot = [](float number) -> float
{
  union Conv
  {
    float f;
    uint32_t i;
  };
  Conv conv;
  conv.f = number;
  conv.i = 0x5f3759df - (conv.i >> 1);
  conv.f *= 1.5F - (number * 0.5F * conv.f * conv.f);
  return 1 / conv.f;
};

auto solve_quadratic_equation = [](double a)
{
  return [a](double b)
  {
    b /= a;
    return [a, b](double c) -> std::pair<std::complex<double>, std::complex<double>>
    {
      c /= a;
      double discriminant = b * b - 4 * c;
      std::complex<double> complex_b(-b / 2, 0);

      if (discriminant < 0)
      {
        double realPart = complex_b.real();
        double imaginaryPart = std::sqrt(-discriminant) / 2;
        std::complex<double> root1(realPart, imaginaryPart);
        std::complex<double> root2(realPart, -imaginaryPart);
        return std::make_pair(root1, root2);
      }

      double root = std::sqrt(discriminant);
      std::complex<double> root1((-b + root) / 2, 0);
      std::complex<double> root2((-b - root) / 2, 0);
      return std::make_pair(root1, root2);
    };
  };
};

int main()
{
  std::pair<complex, complex> result = solve_quadratic_equation(3)(4)(5);
  std::cout << result.first << ", " << result.second << std::endl;
}