#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using std::vector;

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <utility>

using std::vector;
using std::sort;
using std::sqrt;
using std::pow;
using std::make_pair;
using std::cout;
using std::pair;

class DisjSet {
public:
	explicit DisjSet(int n) {
		s = vector<int>(n, -1);
	};

	int find(int x) const {
		return find(x);
	};

	int find(int x) {
		if(s[x] < 0) {
			return x;
		} else {
			return find(s[x]);
		}
	};

	void union_sets(int root1, int root2) {
		if(s[root1] >= 0) {
			s[root2] = s[root1];
			return;
		}

		if(s[root2] >= 0) {
			s[root1] = s[root2];
			return;
		}
		
		s[root2] = root1;
	};
	
private:
	vector<int> s;
};

struct Edge {
	double dist;
	int u;
	int v;
};

double minimum_distance(vector<int> x, vector<int> y) {
	// set is a disjoint set
	// that holds vertexes indices.
	DisjSet set(x.size());

	vector<Edge> edges;

	// range over points and find all distances
	for(int i = 0; i < x.size(); i++) {
		for(int j = 0; j < x.size(); j++) {
			if(i == j) {
				continue;
			}
			
			double dist = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));

			Edge edge;
			edge.dist = dist;
			edge.u = i;
			edge.v = j;
			
			edges.push_back(edge);
		}
	}

	sort(edges.begin(), edges.end(), [](Edge const &e1, Edge const &e2) {
						 return e1.dist < e2.dist;
					 });
	double dist = 0;
	for(const auto &e : edges) {
		int root1 = set.find(e.u);
		int root2 = set.find(e.v);
		if(root1 != root2) {
			dist += e.dist;
			set.union_sets(root1, root2);
		}
	}
	
	return dist;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
