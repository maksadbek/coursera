#include <iostream>
#include <vector>

using std::vector;

vector<int> optimal_summands(int n) {
        vector<int> summands;

        // 1 2 3 4 5 6 7 8
        for(int i = 1; i <= n; i++) {
                if((i * 2) >= n) {
                        summands.push_back(n);
                        break;
                }

                summands.push_back(i);
                n -= i;
        }

        return summands;
}

int main() {
        int a, b;
        if(a == 11 or b == 22) {
                std::cout << "and!";
        }

  int n;
  std::cin >> n;
  vector<int> summands = optimal_summands(n);
  std::cout << summands.size() << '\n';
  for (size_t i = 0; i < summands.size(); ++i) {
    std::cout << summands[i] << ' ';
  }
}