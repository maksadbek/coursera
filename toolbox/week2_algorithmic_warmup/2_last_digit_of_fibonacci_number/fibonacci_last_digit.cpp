#include <iostream>
#include <cassert>

int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

int get_fibonacci_last_digit_fast(int n) {
    if (n <= 1) {
        return n;
    }

    int prev = 0;
    int curr = 1;

    for (int i = 0; i < n-1; ++i) {
        int tmp = curr;
        curr = (prev + curr) % 10;
        prev = tmp;
    }

    return curr;
}


void test_solution() {
    for (int n = 0; n < 20; ++n) {
        int fast = get_fibonacci_last_digit_fast(n);
        int naive = get_fibonacci_last_digit_naive(n);

        assert(fast == naive);
    }
}

int main() {
    int n;
    std::cin >> n;
    int c = get_fibonacci_last_digit_fast(n);
    std::cout << c << '\n';
}
