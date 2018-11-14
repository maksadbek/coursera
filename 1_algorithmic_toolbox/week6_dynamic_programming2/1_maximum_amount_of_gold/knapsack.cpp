#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::max;

int optimal_weight_greedy(int W, const vector<int> &w) {
        //write your code here
        int current_weight = 0;
        for (size_t i = 0; i < w.size(); ++i) {
                if (current_weight + w[i] <= W) {
                        current_weight += w[i];
                }
        }

        return current_weight;
}

int optimal_weight_dp(int W, const vector<int> &w) {
        // create a 2d array
        // x axis is a 1..W
        // y axis is a level of mixed values of w vector.
        // initialize array with 0 values
        // dp is our 2d array.
        vector<vector<int>> dp(w.size()+1, vector<int>(W+1, 0));

        // range over 1..W
        // range over values of w.
        // if value of item less or equal to n
        // then, find the difference weight between n and item,
        // check if adding current item's value to diff weight's value
        // is more than current value.
        for(int i = 1; i <= W; i++) {
                for(int j = 1; j <= w.size(); j++) {
                        dp[j][i] = dp[j-1][i];

                        if(w[j-1] > i) {
                                continue;
                        }
                        auto val = dp[j-1][i-w[j-1]];
                        dp[j][i] = max(dp[j][i], val+w[j-1]);
                }
        }
        
        for(auto x: dp) {
                for(auto y: x) {
                        std::cout << y << " ";
                }
                std::cout << std::endl;
        }

        std::cout << std::endl;

        return dp[w.size()][W];
}

int main() {
        int n, W;
        std::cin >> W >> n;
        vector<int> w(n);
        for (int i = 0; i < n; i++) {
                std::cin >> w[i];
        }

        std::cout << optimal_weight_dp(W, w) << '\n';
}
