//
// Created by maksadbek on 2018-12-22.
//

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>

using namespace std;

int dijkstra(int s, int d, vector<vector<pair<int, int>>> g) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

	vector<int> dist(g.size(), numeric_limits<int>::max());
	vector<int> prev(g.size(), -1);

	//set source distance to 0
	dist[s] = 0;
	q.push(make_pair(dist[s], s));

	while(!q.empty()){
		// Pick the vertex with minimal distance.
		int u = q.top().second;
		q.pop();

		// If the target vertex is reached,
		// then stop traversing.
		if(u==d){
			break;
		}

		for(auto c : g[u]) {
			int v = c.first;
			int w = c.second;

			int alt = dist[u] + w;

			if (alt < dist[v]){
				dist[v] = alt;
				prev[v] = u;

				q.push(make_pair(dist[v], v));
			}
		}
	}

	// generate path sequence
	vector<int> path;
	for(int u = d; prev[u] != -1; u = prev[u]){
		path.push_back(u);
	}

	if(dist[d] == numeric_limits<int>::max()) {
		return -1;
	}

	return dist[d];
}

int main(){
	int n, m;
	std::cin >> n >> m;

	vector<vector<pair<int, int>>> adj(n, vector<pair<int, int>>());

	for (int i = 0; i < m; i++) {
		int x, y, w;
		std::cin >> x >> y >> w;
		adj[x - 1].push_back(make_pair(y - 1, w));
	}

	int s, d;
	std::cin >> s >> d;
	s--, d--;

	int distance = dijkstra(s, d, adj);

	cout << distance;

	return 0;
}

