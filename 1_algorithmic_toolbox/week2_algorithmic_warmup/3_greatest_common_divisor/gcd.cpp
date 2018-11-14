#include <iostream>
#include <cassert>

int gcd_naive(int a, int b) {
  int current_gcd = 1;
  for (int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
      if (d > current_gcd) {
        current_gcd = d;
      }
    }
  }
  return current_gcd;
}

int gcd_fast(int a, int b) {
  while(b > 0) {
    int tmp = b;
    b = a % b;
    a = tmp;
  }

  return a;
}

void test_solution() {
  assert(gcd_fast(18, 35) == gcd_naive(18, 35));
  assert(gcd_fast(28851538, 1183019) == gcd_naive(28851538, 1183019));
}

int main() {
  test_solution();
  int a, b;
  std::cin >> a >> b;
  std::cout << gcd_fast(a, b) << std::endl;
  return 0;
}
