#include <iostream>

using namespace std;

// int
// square (int e)
// {
// 	int dummy=e;
// 	int dummy2=e;
//   for (int i=1;i<dummy2;i++)
//   	{
//   		e=e+dummy;
//   		cout << "i: " << i << " dummy:" << dummy << " e:" << e << endl;
//   	}
//   cout << "square:" << e << endl;
//   return e;
// }

auto square = [](const int e)
{ return e * e; };

auto squareroot = [](double x) -> double
{
  if (x == 0)
    return 0;

  double xhi = x;
  double xlo = 0;
  double guess = x / 2;

  while (std::abs(guess * guess - x) > 0.00001)
  {
    if (guess * guess > x)
    {
      xhi = guess;
    }
    else
    {
      xlo = guess;
    }

    guess = (xhi + xlo) / 2;
  }

  std::cout << "guess: " << guess << std::endl;
  return guess;
};
// void
// pythagoras ()
// {
//   z = squareroot (square (x) + square (y));
//   cout << "euklid:" << z << endl;
// }

auto pythagoras = [](int x)
{
  return [x](int y)
  {
    return squareroot(square(x) + square(y));
  };
};

int main(int argc, char *argv[])
{
  int x = 3;
  int y = 4;
  cout << pythagoras(x)(y) << endl;
  return 0;
}
