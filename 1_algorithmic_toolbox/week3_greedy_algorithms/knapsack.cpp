#include <iostream>
#include <vector>
#include <tuple>
#include <math.h>
#include <iomanip>
#include <algorithm>

// TODO: convert ints to doubles
double knapsack(int w, std::vector<std::pair<double, double>> weights) {
        double L = 0;

        std::sort(weights.begin(), weights.end(), [](std::pair<double, double> a, std::pair<double, double> b) {
                return a.second/a.first > b.second/b.first;
        });

        for(auto weight: weights) {
                int a = std::min(weight.first, double(w));
                double s = a * weight.second/weight.first;

                L += s;
                w -= a;
        }

        return L;
}

int main() {
        int w, n;

        std::cin >> n >> w;

        std::vector<std::pair<double, double>> weights;
        for(int i = 0; i < n; i++) {
                int weight, value;
                std::cin >> value >> weight;

                weights.push_back(std::make_pair(weight, value));
        }

        double result = knapsack(w, weights);
        std::cout << std::fixed << std::setprecision(4)<< result << std::endl;
}