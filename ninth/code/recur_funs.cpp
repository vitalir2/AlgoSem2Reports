#include <cmath>
#include <iostream>

constexpr long double h = 0.00000001; // 10^-8

double newtonsMethodRoot(double N, double x, double n) {
  double xn = 1/n * ((n-1)*x+N/std::pow(x, n-1));
  if (std::fabs(xn - x) <= h) {
    return xn;
  } else {
    return newtonsMethodRoot(N, xn, n);
  }
}

double newtonsMethodRootIter(double N, double x, double n) {
  double xn = 0;
  double xprev = x;
  for (;;) {
    xn = 1/n * ((n-1)*xprev+N/std::pow(xprev, n-1));
    if (std::fabs(xprev - xn) <= h) {
      break;
    }
    xprev = xn;
  }
  return xn;
}

int main() {
  std::cout << "Enter number which will be calculated: ";
  int N;
  std::cin >> N;
  std::cout << "Enter power of root function: ";
  int power;
  std::cin >> power;
  double res = newtonsMethodRoot(N, N, power);
  std::cout << power << " power root = " << res
    << '\n';
  return 0;
}
