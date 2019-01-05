#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <algorithm>
#include <iterator>
#include <set>
#include <queue>
#include <utility>

using namespace std;

typedef pair<long long, int> int_pair;

const long long inf = numeric_limits<long long>::max() / 4;
const bool verbose = false;

long long shortest_path(int s, int t, const vector<long long> &dist, const vector<long long> &dist_r, set<int> proc) {
	auto distance = inf;
	for(auto v : proc) {
		if(dist[v] + dist_r[v] > inf) {
			continue;
		}
		
		distance = min(dist[v] + dist_r[v], distance);
		if(verbose) {
			printf("shortest_path - v: %d, dist: %lld\n", v, dist[v] + dist_r[v]);
		}
	}

	if(distance == inf) {
		return -1;
	}
	
	return distance;
};

vector<long long> dist;
vector<long long> dist_r;

priority_queue<int_pair, vector<int_pair>, greater<int_pair>> q;
priority_queue<int_pair, vector<int_pair>, greater<int_pair>> q_r;

long long bidijkstra(const vector<vector<int_pair>> &adj, const vector<vector<int_pair>> &adj_r, int s, int t) {
	dist[s] = 0;
	dist_r[t] = 0;



	q.push(make_pair(0, s));
	q_r.push(make_pair(0, t));
	
	set<int> proc;
	while(true) {
		v = q.top();
		q.pop();
		
		if(verbose) {
			printf("min: %d\n", v.second);
		}

		if(v.first == inf) {
			continue;
		}

		for(auto e : adj[v.second]) {
			if(verbose) {
				printf("adj of %d: %d\n", v.second, e.second);
			}
			
			auto d = e.first + v.first;
			if(d < dist[e.second]) {
				q.push(make_pair(d, e.second));
				dist[e.second] = d;
				if(verbose) {
					printf("dist to %d: %lld\n", e.second, dist[e.second]);
				}
			}
		}
		
		if(!proc.insert(v.second).second) {
			return shortest_path(s, t, dist, dist_r, proc);
		}

		// reverse
		auto v_r  = q_r.top();
		q_r.pop();
		if(verbose) {
			printf("reverse min: %d\n", v_r.second);
		}
		
		if(dist_r[v_r.second] == inf) {
			continue;
		}

		for(auto e : adj_r[v_r.second]) {
 			if(verbose) {
				printf("reverse adj of %d: %d\n", v_r.second, e.second);
			}
			
			auto d = e.first + v_r.first;
			if(d < dist_r[e.second]) {
				dist_r[e.second] = d;
				q_r.push(make_pair(d, e.second));
				
				if(verbose) {
					printf("reverse dist to %d: %lld\n", e.second, dist_r[e.second]);
				}
			}
		}
		
		if(!proc.insert(v_r.second).second) {
			return shortest_path(s, t, dist, dist_r, proc);
		}
	}

	return -1;
}

vector<vector<int_pair>> adj;
vector<vector<int_pair>> adj_r;

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	adj.resize(n);
	adj_r.resize(n);
	
	for (int i=0; i<m; ++i) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		
		adj[u-1].push_back(make_pair(c, v-1));
		adj_r[v-1].push_back(make_pair(c, u-1));
	}

	int t;
	scanf("%d", &t);
	for (int i=0; i<t; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%lld\n", bidijkstra(adj, adj_r, u-1, v-1));
	}
}
