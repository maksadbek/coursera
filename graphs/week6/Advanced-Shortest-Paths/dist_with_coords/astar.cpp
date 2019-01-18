#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

const int inf = numeric_limits<int>::max();

class Astar {
public:
	vector<vector<pair<int,int>>> g;
	vector<pair<int,int>> coords;
	
	double heuristic_potential(int v1, int v2) {
		auto delta1 = pow(coords[v1].first - coords[v2].first, 2);
		auto delta2 = pow(coords[v1].second - coords[v2].second, 2);
		return sqrt(delta1 + delta2);
	}


	Astar(int n) {
		g.resize(n);
		coords.resize(n);
	}

	// run returns the shortest path.
	double query(int s, int t) {
		if(s == t) {
			return 0;
		}
		vector<long long> heur(g.size());
		vector<long long> dist(g.size(), inf);
		vector<int> discovered(g.size(), false);
		priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
		
		heur[s] = 0;
		dist[s] = 0;
		pq.push(make_pair(0, s));

		while(!pq.empty()) {
			auto u = pq.top();
			pq.pop();
			
			auto current = u.second;

			for(auto &v: g[current]) {
			        auto cost = dist[current] + v.second;
				auto neighbor = v.first;
				
				if(cost < dist[neighbor] or !discovered[neighbor]) {
				        dist[neighbor] = cost;
					auto h = heuristic_potential(neighbor, t);
					heur[neighbor] = h + cost;
					pq.push(make_pair(h+cost, neighbor));
					discovered[neighbor] = true;
				}
			}
		}

		if(dist[t] == inf) {
			return -1;
		}
		
		return dist[t];
	}
};

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	
	Astar astar(n);
	
	for (int i=0; i<n; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		astar.coords[i] = make_pair(x, y);
	}
	

	
	for (int i = 0; i < m; i++) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);

		astar.g[u-1].push_back(make_pair(v-1, c));
	}



	int t;
	scanf("%d", &t);
	for (int i=0; i<t; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		int dist = astar.query(u-1, v-1);
		printf("%d\n", dist);
	}
}
