#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>
#include <functional>

using std::vector;
using std::function;
using std::pair;
using std::make_pair;
using std::string;

template<typename T>
class MinHeap {
public:
	MinHeap() {}

	MinHeap(function<bool(T, T)> less) : less(less) {}

	MinHeap(vector<T> data): h(data) {
		for(int i = std::ceil(data.size()/2-1); i >= 0 ; i--) {
			sift_down(i);
		}
	}

	int push(T value) {
		h.push_back(value);
		return sift_up(h.size()-1);
	}

	int pop() {
		if(h.empty()) {
			return -1;
		}

		T result = h[0];
		h[0] = h.back();
		h.pop_back();

		sift_down(0);

		return result;
	}

	int remove(T val) {
		int node = -1;
		for(int i = 0; i < h.size(); i++) {
			if(h.at(i) == val) {
				node = i;
				break;
			}
		}

		if(node == -1) {
			return -1;
		}

		h[node] = -1;
		sift_up(node);
		pop();
	}

	int change_priority(T val, int priority) {
		int node = -1;
		for(int i = 0; i < h.size(); i++) {
			if(h[i] == val) {
				node = i;
				break;
			}
		}

		if(node == -1) {
			return -1;
		}

		T old = h[node];

		int result_node = node;

		h[node] = priority;

		if(priority < old) {
			result_node = sift_up(node);
		} else {
			result_node = sift_down(node);
		}

		return result_node;
	}
private:
	std::vector<T> h;
	function<bool(T, T)> less = [](T t1, T t2) { return t1 < t2; };

	int parent(int node) {
		if(node == 0) {
			return 0;
		}

		return std::ceil(float(node) / float(2)) - 1;
	}

	int left_child(int node) {
		return node * 2 + 1;
	}

	int right_child(int node) {
		return node * 2 + 2;
	}

	// sift_up moves up the node until his parent is not greater than him
	// or it does not reach the root.
	int sift_up(int node) {
		while(node >= 0 and h[parent(node)] > h[node]) {
			std::swap(h[parent(node)], h[node]);
			node = parent(node);
		}

		return node;
	}

	// sift_down move the node down until its right and light children are lower
	// than him.
	int sift_down(int node) {
		int min_index = node;

		int l = left_child(node);
		while(l < h.size() and h[l] < h[min_index]) {
			min_index = l;
		}

		int r = right_child(node);
		while(r < h.size() and h[r] < h[min_index]) {
			min_index = r;
		}

		if(h[min_index] != h[node]) {
			std::swap(h[min_index], h[node]);
			sift_down(min_index);
		}

		return min_index;
	}
};

int main(int argc, char** argv) {
	MinHeap<pair<int, string>> min_heap;
	min_heap.push(make_pair(5, "tokyo"));
	min_heap.push(make_pair(4, "ny"));
	min_heap.push(make_pair(3, "moscow"));
	min_heap.push(make_pair(2, "dubai"));
	min_heap.push(make_pair(1, "tashkent"));

	min_heap.print();

	printf("min: %d ->", min_heap.pop());
	min_heap.print();

	printf("min: %d ->", min_heap.pop());
	min_heap.print();

	printf("min: %d ->", min_heap.pop());
	min_heap.print();

	min_heap.change_priority(5, 1);
	printf("min: %d ->", min_heap.pop());
	min_heap.print();

	return 0;
}