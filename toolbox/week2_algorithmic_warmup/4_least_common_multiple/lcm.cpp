#include <iostream>
#include <cassert>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

int gcd_fast(int a, int b) {
  while(b > 0) {
    int tmp = b;
    b = a % b;
    a = tmp;
  }

  return a;
}

long long lcm_fast(int a, int b) {
  long long along = a;
  long long blong = b;

  long long m = along * blong;

  return m / gcd_fast(a,b);
}

void test_solution() {
  assert(lcm_fast(6, 8) == lcm_naive(6, 8));

  long long fast = lcm_fast(28851538, 1183019);
  long long naive = lcm_naive(28851538, 1183019);
  std::cout << fast <<";" << naive << std::endl;
  assert(fast == naive);
}

int main() {
  // test_solution();

  int a, b;
  std::cin >> a >> b;
  std::cout << lcm_fast(a, b) << std::endl;
  return 0;
}
