#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>

template<typename T>
class Heap {
        public:
                Heap(int n) {
                        h = std::vector<T>(n);
                        size = 0;
                }
                
                void print() {
                        for(int i = 0; i < size-1; i++) {
                                std::cout << h[i] << " ";
                        }

                        std::cout << h[size-1] << std::endl;
                }

                int parent(int node) {
                        int p = std::ceil(node / 2);
                        // std::cout << "parent of " << node << " = " << p << std::endl;
                        return p;
                }

                int left_child(int node) {
                        return std::max(node, 1) * 2 - 1;
                }

                int right_child(int node) {
                        return std::max(node, 1) * 2;
                }

                // sift_up moves up the node until his parent is not greater than him
                // or it does not reach the root.
                int sift_up(int node) {
                        while(node >= 0 and h[parent(node)] > h[node]) {
                                std::cout << parent(node) << " " << node << std::endl;
                                std::swap(h[parent(node)], h[node]);
                                node = parent(node);
                        }

                        return node;
                }

                // sift_down move the node down until its right and light children are lower
                // than him.
                int sift_down(int node) {
                        int max_index = h[node];

                        int l = max_index;
                        while(l > h.size() and h[l] < h[max_index]) {
                                max_index = h[l];
                        }

                        int r = max_index;
                        while(r > h.size() and h[r] < h[max_index]) {
                                max_index = h[r];
                        }

                        if(h[max_index] != h[node]) {
                                std::swap(h[max_index], h[node]);
                                sift_down(h, max_index);
                        }

                        return max_index;
                }

                int insert(T value) {
                        if(size == h.size()-1) {
                                return -1;
                        }
                        h[size] = value;

                        auto node = sift_up(size);
                        size++;

                        return node;
                }

                int pop_max() {
                        int result = h[0];
                        size--;
                        h[0] = h[size];
                        sift_down(0 /* root node */);

                        return result;
                }

                int remove(int node) {
                        h[node] = std::numeric_limits<int>::max();
                        sift_up(node);
                        pop_max();
                }

                int change_priority(int node, int priority) {
                        int old = h[node];
                        int result_node = node;

                        h[node] = priority;
                        if(priority < old) {
                                result_node = sift_up(node);
                        } else {
                                result_node = sift_down(node);
                        }

                        return result_node;
                }

                void build_from_array(std::vector<T> data) {
                        for(int i = 0; i < data.size(); i++) {
                                size++;
                                h[i] = data[i];
                        }

                        // print();
                        for(int i = data.size()-1; i >= 0; i--) {
                                // std::cout << "sifting up: " << h[i] << std::endl;
                                sift_up(i);
                                // std::cout << "result after sift-up ";
                                // print();
                        }
                }
        private:
                int size = 0;
                std::vector<T> h;
};

int main(int argc, char** argv) {
        /*
        std::cout << std::ceil(1 / 2) << std::endl;
        std::cout << std::ceil(3 / 2) << std::endl;
        return 0;
        */

        Heap<int> heap(15);

        heap.build_from_array(std::vector<int>{5,4,3,2,1});
        heap.print();

        return 0;
}