#include <iostream>
using namespace std;


int calculateSqaureHelper(const int i, const int e, const int dummy){
  if(i<dummy){
    return calculateSqaureHelper(i+1, e+dummy, dummy);
  }

  return e; 
}


int square (const int e)
{
	// int dummy=e;
	// int dummy2=e;
  // for (int i=1;i<dummy2;i++)
  // 	{
  // 		e=e+dummy;
  // 		cout << "i: " << i << " dummy:" << dummy << " e:" << e << endl;
  // 	}
  // cout << "square:" << e << endl;
  return calculateSqaureHelper(1,e,e);
}


double calculate(const double guess, const double x, const double xhi, const double xlo)
{

  double newXhi = xhi;
  double newXlo = xlo;

  if (abs(guess * guess - x) > 0.00001)
  {
    if (guess * guess > x)
    {
      newXhi = guess;
    }
    else
    {
      newXlo = guess;
    }

    double newGuess = (newXhi+newXlo)/2;

    return calculate(newGuess, x, newXhi, newXlo);
  }
  else
  {
    return guess;
  }

  return 0;
}

double squareroot(const double x)
{ /* computes the square root of x */

  if (x == 0)
    return 0;


  /* the sqrt must be between xhi and xlo */

  /* We stop when guess*guess-x is very small */

  return calculate(x / 2, x, x, 0);

  // cout << "guess:" << guess << endl;
}

double pythagoras(const int x, const int y)
{
  return squareroot(square(x) + square(y));
  // cout << "euklid:" << z << endl;
}

int main(int argc, char *argv[])
{
  int x = 3;
  int y = 4;
  double z = pythagoras(x, y);
  cout << z << endl;
  return 0;
}
