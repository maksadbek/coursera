#include <iostream>

// greedy choice: always choose the greatest number from m
// safe move: always subtract the greatest number from m.
int naive_get_change(int m) {
        int changes_count = 0;
        int changes[] = {10, 5, 1};

        while(m > 0) {
                for(int i = 0; i < 3; i++) {
                        if(m >= changes[i]) {
                                m -= changes[i];
                                changes_count++;
                                break;
                        }
                }
        }

        return changes_count;

}

int main() {
        int m;
        std::cin >> m;
        std::cout << naive_get_change(m) << '\n';
}