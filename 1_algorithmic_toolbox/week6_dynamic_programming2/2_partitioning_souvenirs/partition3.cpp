#include <iostream>
#include <vector>

using std::vector;

int partition3(vector<int> &A) {
        printf("hehehe\n");
        if(A.size() < 3) {
                return 0;
        }

        int sum = 0;
        for(auto x: A) {
                sum += x;
        }
        printf("sum: %d\n", sum);
        // return 0;

        if(sum % 3 != 0) {
                return 0;
        }
        int third = sum / 3;
        vector<vector<vector<int>>> dp(third, vector<vector<int>>(sum, vector<int>(sum, 0)));
        int i = 0, j = 0, k = 0;

        for(k = 2; k < third; k++) {
                printf("blet3\n");
                for(i = 0; i < sum; i++) {
                        printf("blet2\n");
                        for(j = 0; j < sum; j++) {
                                printf("blet: i: %d, k: %d\n", i, k);
                                int tmp1 = 0;
                                if(A[k-1] <= i) {
                                        tmp1 = dp[k-1][i-A[k-1]][j];
                                }

                                int tmp2 = 0;
                                if(A[k-1] <= j) {
                                        tmp2 = dp[k-1][i][j - A[k-1]];
                                }
                        }
                }
        }

        return dp[k-1][i-1][j-1];
}

int main() {
        int n;
        std::cin >> n;
        vector<int> A(n);

        for (size_t i = 0; i < A.size(); ++i) {
                std::cin >> A[i];
        }

        std::cout << partition3(A) << '\n';
}
