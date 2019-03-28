#include <iostream>
#include <vector>

using std::vector;

bool partition2(vector<int> A) {
        // if there are less than 2 elements
        // then it is not possible to partition them into 2 parts.
        if(A.size() < 2) {
                return false;
        }

        // calculate the sum to split it in halve.
        int sum = 0;
        for(auto x : A) {
                sum += x;
        }
        // if sum is not divisible into 2,
        // then it is again impossible to partition them into 2 parts.
        if(sum % 2 != 0) {
                return false;
        }

        int half = sum / 2;
        vector<vector<bool>> dp(A.size()+1, vector<bool>(half+1, false));
        dp[0][0] = true;

        for(int i = 1; i <= half; i++) {
                for(int j = 1; j <= A.size(); j++) {
                        if(A[j-1] > i) {
                                continue;
                        }

                        // check if current value is eq to i;
                        if((A[j-1] == i) or dp[j-1][i]) {
                                dp[j][i] = true;
                        } else if(dp[j-1][i-A[j-1]]) {
                                dp[j][i] = true;
                        }
                }
        }

        for(auto x : dp) {
                for(auto y : x) {
                        std::cout << std::boolalpha<<  y << " ";
                }
                std::cout << std::endl;
        }        

        return dp[A.size()][half];
}

int main() {
        // printf("%d\n", partition2({3, 3, 1, 2, 2, 1}));
        printf("%d\n", partition2({3, 3, 3, 3}));
}