#include <iostream>
#include <vector>

using std::vector;

long long get_number_of_inversions(vector<int> &a, size_t left, size_t right) {
        long long number_of_inversions = 0;
        if (right <= left + 1) return number_of_inversions;
        size_t ave = left + (right - left) / 2;
        number_of_inversions += get_number_of_inversions(a, left, ave);
        number_of_inversions += get_number_of_inversions(a, ave, right);

        // std::cout << left << " " << ave << " " << right << std::endl;
        vector<int> leftv;
        vector<int> rightv;

        for(int i = left; i < ave; i++) {
                leftv.push_back(a[i]);
        }

        for(int i = ave; i < right; i++) {
                rightv.push_back(a[i]);
        }

        /*
        std::cout << "left: ";
        for(auto x: leftv) {
                std::cout << x << ",";
        }

        std::cout << "right: ";
        for(auto x: rightv) {
                std::cout << x << ",";
        }

        std::cout << std::endl;
        */

        int l = 0, r = 0, c = 0;
        for(int i = left; i < right; i++) {
                // std::cout << ">" << i << " l:" << l << " r:" << r << std::endl;
                if(r >= rightv.size()) {
                        a[i] = leftv[l];
                        l++;
                } else if (l >= leftv.size()) {
                        a[i] = rightv[r];
                        r++;
                } else if (leftv[l] <= rightv[r]) {
                        a[i] = leftv[l];
                        l++;
                } else {
                        a[i] = rightv[r];
                        r++;

                        number_of_inversions += int(leftv.size() - l);
                }
        }

        return number_of_inversions;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }

        std::cout << get_number_of_inversions(a, 0, a.size())<< '\n';
        // for(auto x : a) std:: cout << x << ", ";
}