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

double clustering(vector<int> x, vector<int> y, int k) {
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

	double dist;
	vector<double> mst_distances;
	for(const auto &e : edges) {
		int root1 = set.find(e.u);
		int root2 = set.find(e.v);
		
		if(root1 != root2) {
			mst_distances.push_back(e.dist);
			set.union_sets(root1, root2);
		}
	}

	auto sort_fn = [](double const &a, double const &b){ return a > b; };
	sort(mst_distances.begin(), mst_distances.end(), sort_fn);

	return mst_distances[k-2];
}


int main() {
	size_t n;
	int k;
	std::cin >> n;
	vector<int> x(n), y(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> y[i];
	}
	
	std::cin >> k;
	std::cout << std::fixed << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
