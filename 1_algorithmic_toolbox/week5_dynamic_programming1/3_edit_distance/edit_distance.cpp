#include <iostream>
#include <string>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;
using std::min;

int edit_distance(const string &str1, const string &str2) {
        int dp[str1.size()+1][str2.size()+1];

        for(int i = 0; i <= str1.size(); i++) {
                dp[i][0] = i;
        }

        for(int i = 0; i <= str2.size(); i++) {
                dp[0][i] = i;
        }

        for(int i = 1; i <= str1.size(); i++) {
                for(int j = 1; j <= str2.size(); j++) {
                        int insertion = dp[i][j-1] + 1;
                        int deletion = dp[i-1][j] + 1;
                        int match = dp[i-1][j-1];
                        int mismatch = dp[i-1][j-1] + 1;

                        if(str1[i-1] == str2[j-1]) {
                                // printf("%c %c, %d %d\n", str1[i-1], str2[j-1], i, j);
                                dp[i][j] = min({insertion, deletion, match});
                        } else {
                                dp[i][j] = min({insertion, deletion, mismatch});
                        }
                }
        }

        /*
        for(int i = 0; i < str1.size(); i++) {
                for(int j = 0; j < str2.size(); j++) {
                        cout << dp[i][j] << " ";
                }
                cout << endl;
        }
        */

        return dp[str1.size()][str2.size()];
}

int main() {
        string str1;
        string str2;
        std::cin >> str1 >> str2;
        std::cout << edit_distance(str1, str2) << std::endl;
        return 0;
}