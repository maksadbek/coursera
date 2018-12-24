#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

/*
        0
      1   2
     3 4 5 6
       

        5
      4   3
     2 1    

        3
      4   5
     5 1    

        3
      1   5
     5 4    
*/
int parent(int node) {
        return std::ceil(float(node) / float(2)) - 1;
}
 
int left_child(int node) {
        return node * 2 + 1;
}

int right_child(int node) {
        return node * 2 + 2;
}


int sift_up(vector<int> &h, int node, vector<pair<int,int>> &swaps) {
        while(node >= 0 and h[parent(node)] > h[node]) {
                swaps.push_back(make_pair(parent(node), node));

                std::swap(h[parent(node)], h[node]);
                node = parent(node);
        }

        return node;
}

int sift_down(vector<int> &h, int node, vector<pair<int,int>> &swaps) {
        int min_index = node;

        int l = left_child(node);

        if(l < h.size() and h[l] < h[min_index]) {
                min_index = l;
        }

        int r = right_child(node);
        if(r < h.size() and h[r]  < h[min_index]) {
                min_index = r;
        }

        if(h[min_index] != h[node]) {
                std::swap(h[min_index], h[node]);

                swaps.push_back(make_pair(node, min_index));
                sift_down(h, min_index, swaps);
        }

        return min_index;
}

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void GenerateSwaps() {
    swaps_.clear();

    for(int i = std::ceil(data_.size()/2); i >= 0 ; i--) {
	sift_down(data_, i, swaps_);
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
