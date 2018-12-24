#include <iostream>
#include <vector>
#include <limits>

using std::vector;
using std::numeric_limits;

const int max_int = numeric_limits<int>::max();

int negative_cycle(vector<vector<int>> &adj, vector<vector<int>> &cost) {
	vector<int> dist(adj.size(), 0 /* max_int */);
	// dist[0] = 0;

	for(int i = 0; i < adj.size() - 1; i++) {
		for(int u = 0; u < adj.size(); u++) {
			for(int v : adj[u]) {
				int w = cost[u][v];

				if(/*dist[u] != max_int && */ (w + dist[u]) < dist[v]) {
					dist[v] = w + dist[u];
				}
			}
		}
	}

	// check for cycles
	for(int u = 0; u < adj.size(); u++) {
		for(int v : adj[u]) {
			int w = cost[u][v];

			if(/* dist[u] != max_int && */(w + dist[u] < dist[v])) {
				return 1;
			}
		}
	}

	return 0;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	vector<vector<int> > cost(n, vector<int>(n));
	for (int i = 0; i < m; i++) {
		int x, y, w;
		std::cin >> x >> y >> w;
		adj[x - 1].push_back(y - 1);
		cost[x - 1][y - 1] = w;
	}

	std::cout << negative_cycle(adj, cost);
}
