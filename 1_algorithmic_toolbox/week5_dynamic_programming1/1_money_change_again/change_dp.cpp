#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

int get_change(int m) {
        int dp[m+1];
        dp[0] = 0;
        dp[1] = 1;

        std::array<int, 3> coins = {1, 3, 4};

        for(int i = 2; i <= m; i++) {
                std::vector<int> values;
                for(int j=0; coins[j] <= i and j < coins.size(); j++) {
                        values.push_back(dp[i-coins[j]] + 1);
                        // std::cout << i << ":" << i - coins[j] << std::endl;
                }

                /*
                        printf("%d : ", i);
                        for(auto x : values) {
                                printf("%d, ", x);
                        }
                        printf("\n");
                */

                auto it = std::min_element(values.begin(), values.end());
                // std::cout << "min: " << *it << std::endl;
                dp[i] = *it;
        }

        return dp[m];
}

int main() {
        int m;
        std::cin >> m;
        std::cout << get_change(m) << '\n';
}
