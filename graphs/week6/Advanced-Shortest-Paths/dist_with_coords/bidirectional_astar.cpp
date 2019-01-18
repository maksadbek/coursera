#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;

const long long inf = numeric_limits<long long>::max() / 4;

class astar {
	vector<pair<int,int>> &coords;
	priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> q[2];
	vector<long long> f[2];
	vector<long long> g[2];
	set<int> proc[2];

	const int forward = 0;
	const int backward = 1;

	vector<vector<vector<pair<int,int>>>> adj;
  
	double estimate(int v1, int v2) {
		auto delta1 = pow(coords[v1].first - coords[v2].first, 2);
		auto delta2 = pow(coords[v1].second - coords[v2].second, 2);
		return sqrt(delta1 + delta2);
	}

	double shortest_path(int s, int t) {
		set<int> common_vertices;
		merge(proc[0].begin(), proc[0].end(),
		      proc[1].begin(), proc[1].end(),
		      inserter(common_vertices, common_vertices.begin()));

		auto dist = inf;
		for(int i : common_vertices) {
			long long new_dist = g[0][i] + g[1][i];
			if(new_dist < dist) {
				dist = new_dist;
			}
		}

		if(dist==inf) {
			return -1;
		}
				
		
		return dist;
	}

	void visit(int side, int u, int s, int t) {
		for(auto &v: adj[side][u]) {
			auto neighbor = v.first;
			auto cost = g[side][u] + v.second;
			if(cost < g[side][neighbor]) {
				g[side][neighbor] = cost;

				auto e = (estimate(s, neighbor) + estimate(neighbor, t))/2;
				if(side == backward) {
					e = -e;
				}

				auto heur_cost = e + cost;
				f[side][neighbor] = heur_cost;
				q[side].push(make_pair(heur_cost, neighbor));
			}
		}
	}

	bool pop_and_relax(int side, int s, int t) {
		if(q[side].empty()) {
			return false;
		}

		auto u = q[side].top();
		q[side].pop();
		visit(side, u.second, s, t);
                proc[side].insert(u.second);
                
		if(proc[!side].find(u.second) != proc[!side].end()) {
			return true;
		}

		return false;
	}

	void init() {
		g[forward].resize(adj[forward].size(), inf);
		g[backward].resize(adj[forward].size(), inf);

		f[forward].resize(adj[forward].size(), 0);
		f[backward].resize(adj[forward].size(), 0);
	}

	void clear() {
		g[forward].assign(adj[forward].size(), inf);
		g[backward].assign(adj[forward].size(), inf);

		f[forward].assign(adj[forward].size(), 0);
		f[backward].assign(adj[forward].size(), 0);

		q[forward] = priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>>();
		q[backward] = priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>>();

		proc[forward].clear();
		proc[backward].clear();
			
	}
public:
	astar(vector<vector<vector<pair<int,int>>>> graph, vector<pair<int,int>> &coords): coords(coords) {
		adj = graph;
		init();
	};
  
	// run returns the shortest path.
	long long query(int s, int t) {
		if(s == t) {
			return 0;
		}

		clear();
		
		g[forward][s] = 0;
		f[forward][s] = 0;
		q[forward].push(make_pair(0, s));

		g[backward][t] = 0;
		f[backward][t] = 0;
		q[backward].push(make_pair(0, t));

		while(!q[forward].empty() and !q[backward].empty()) {
			if(pop_and_relax(forward, s, t)) {
				return shortest_path(s, t);
			}

			if(pop_and_relax(backward, s, t)) {
				return shortest_path(s, t);
			}
		}

		return -1;
	}
};

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	
	vector<pair<int,int>> coords(n);
	for (int i=0; i<n; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		coords[i] = make_pair(a,b);
	}

	vector<vector<vector<pair<int,int>>>> adj(2, vector<vector<pair<int,int>>>(n));
	for (int i=0; i<m; i++) {
		int u, v, c;
		
		scanf("%d%d%d", &u, &v, &c);
		adj[0][u-1].push_back(make_pair(v-1, c));
		adj[1][v-1].push_back(make_pair(u-1, c));
	}

	astar as(adj, coords);
	
	int t;
	scanf("%d", &t);
	for (int i=0; i<t; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%lld\n", as.query(u-1, v-1));
	}

	return 0;
}
