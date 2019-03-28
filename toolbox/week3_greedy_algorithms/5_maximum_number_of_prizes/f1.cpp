#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int naive(std::vector<unsigned int> initial_scores, std::vector<unsigned int> final_scores, int n) {
        auto max_score = final_scores[0] + initial_scores[n];

        n-=1;
        int score = n;
        for(int i = 1; (n >= 0) and (i < final_scores.size()); i++) {
                auto cal = final_scores[i] + initial_scores[n];
                std::cout << cal << "<=" << max_score << std::endl;
                if(cal <= max_score) {
                        n--;
                        score--;
                        if(score < 0) {
                                break;
                        }
                }
        }

        return score + 2;
}

int main() {
        std::vector<unsigned int> initial_scores;
        std::vector<unsigned int> final_scores;

        int count, n;
        std::cin >> count >> n;

        for(int i = 0; i < count; i++) {
                int t;
                std::cin >> t;

                initial_scores.push_back(t);
        }

        for(int i = 0; i < count; i++) {
                int t;
                std::cin >> t;
                final_scores.push_back(t);
        }

        std::cout<<naive(initial_scores, final_scores, n-1);
        return 0;
}