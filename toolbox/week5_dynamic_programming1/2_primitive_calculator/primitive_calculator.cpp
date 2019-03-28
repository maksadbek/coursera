#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

using std::vector;

vector<int> optimal_sequence(int n) {
  std::vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

std::tuple<int, vector<int>> optimal_sequence2(int n) {
        int dp[n+1];
        dp[0] = 0;
        dp[1] = 0;

        vector<int> sequence(n+1);
        sequence[1] = 1;

        for(int i = 2; i <= n; i++) {
                dp[i] = dp[i-1] + 1;
                int v = i-1;
                if(i % 2 == 0) {
                        dp[i] = std::min(dp[i], dp[i/2]+1);
                        if(dp[i] == dp[i/2]+1) {
                                v = i/2;
                        }

                }

                if(i % 3 == 0) {
                        dp[i] = std::min(dp[i], dp[i/3]+1);
                        if(dp[i] == dp[i/3]+1) {
                                v = i/3;
                        }
                }

                sequence[i] = v;
        }

        return std::make_tuple(dp[n], sequence);
}

int main() {
        int n;
        std::cin >> n;
        int result;
        vector<int> sequence;

        std::tie(result, sequence) = optimal_sequence2(n);
        std::cout << result << std::endl;

        std::vector<int> v;
        v.push_back(n);
        int i = sequence[n];
        v.push_back(i);

        while(i > 1) {
                i = sequence[i];
                v.push_back(i);
        }

        std::reverse(v.begin(), v.end());
        for(auto x : v) {
                std::cout << x << " ";
        }
}