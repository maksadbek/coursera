#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using std::vector;

int get_majority_element(vector<int> &a, int left, int right) {
        std::cout << "inputs: " << "left:" << left << " right:" << right << std::endl;
        if (left == right) {
                return a[right];
        }

        if (left + 1 == right) {
                return a[left];
        }

        int mid = left + (right - left)/2;
        int result_left = get_majority_element(a, left, mid);
        int result_right = get_majority_element(a, mid, right);

        std::cout << "left: "<< left << " right: " << right << " mid: " << mid << std::endl;
        std::cout << "result_left: " << result_left << " result_right: " << result_right << std::endl;

        if (result_left == result_right) {
                return result_left;
        }

        return -1;
}

int main() {
        int n;
        std::cin >> n;
        vector<int> a(n);
        for (size_t i = 0; i < a.size(); ++i) {
                std::cin >> a[i];
        }

        std::cout << (get_majority_element(a, 0, a.size()) != -1) << '\n';
}
