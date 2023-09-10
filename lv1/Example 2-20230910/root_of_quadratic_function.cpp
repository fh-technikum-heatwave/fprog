#include <iostream>
#include <utility>
#include <complex>

typedef std::complex<double> complex;

double calculateSqaureHelper(const int i, const double e, const double dummy)
{
  if (i < dummy)
  {
    return calculateSqaureHelper(i + 1, e + dummy, dummy);
  }

  return e;
}

double square(const double e)
{
  // int dummy=e;
  // int dummy2=e;
  // for (int i=1;i<dummy2;i++)
  // 	{
  // 		e=e+dummy;
  // 		cout << "i: " << i << " dummy:" << dummy << " e:" << e << endl;
  // 	}
  // cout << "square:" << e << endl;
  return calculateSqaureHelper(1, e, e);
}

inline float squareroot(const float number)
{
  union Conv
  {
    float f;
    uint32_t i;
  };
  Conv conv;
  conv.f = number;
  conv.i = 0x5f3759df - (conv.i >> 1);
  // conv.f *= 1.5F - (number * 0.5F * conv.f * conv.f);
  // return 1/ conv.f;
  return 1 / (conv.f * (1.5F - (number * 0.5F * conv.f * conv.f)));
}

std::pair<complex, complex>
solve_quadratic_equation(const double a, const double b, const double c)
{

  double newB = b / a;
  double newC = c / a;
  double discriminant = square(newB) - 4 * newC;
  if (discriminant < 0)
    return std::make_pair(complex(-newB / 2, squareroot(-discriminant) / 2),
                          complex(-newB / 2, -squareroot(-discriminant) / 2));

  double root = std::sqrt(discriminant);
  double solution1 = (newB > 0) ? (-newB - root) / 2
                             : (-newB + root) / 2;

  return std::make_pair(solution1, newC / solution1);
}

int main()
{
  std::pair<complex, complex> result = solve_quadratic_equation(3, 4, 5);
  std::cout << result.first << ", " << result.second << std::endl;
}