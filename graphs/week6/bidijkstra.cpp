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
const bool debug = true;

vector<vector<int_pair>> adj;
vector<vector<int_pair>> adj_r;

set<int> proc;

long long shortest_path(int s, int t, vector<long long> &dist, vector<long long> &dist_r) {
	auto distance = inf;
	for(auto v : proc) {
		auto d = dist[v] + dist_r[v];
		if(d > inf || d < 0) {
			continue;
		}

		if(d <= distance) {
			distance = d;
		}
	}

	if(distance == inf) {
		return -1;
	}
	
	return distance;
};

long long bidijkstra(int s, int t) {
	proc.clear();
	
	vector<long long> dist(adj.size(), inf);
	vector<long long> dist_r(adj.size(), inf);
	dist[s] = 0;
	dist_r[t] = 0;
	
	priority_queue<int_pair, vector<int_pair>, greater<int_pair>> q;
	q.push(make_pair(0, s));

	priority_queue<int_pair, vector<int_pair>, greater<int_pair>> q_r;
	q_r.push(make_pair(0, t));
	
	while(true) {
		auto v = q.top();
		q.pop();

		if(v.first==inf) {
		  continue;
		}
		
		for(auto e : adj[v.second]) {
			auto d = e.first + v.first;
			if(d < dist[e.second]) {
				q.push(make_pair(d, e.second));
				dist[e.second] = d;
			}
		}
		
		if(!proc.insert(v.second).second) {
			return shortest_path(s, t, dist, dist_r);
		}

		auto v_r  = q_r.top();
		q_r.pop();

		if(v_r.first == inf) {
		  continue;
		}
		for(auto e : adj_r[v_r.second]) {
			auto d = e.first + v_r.first;
			if(d < dist_r[e.second]) {
				dist_r[e.second] = d;
				q_r.push(make_pair(d, e.second));
			}
		}
		
		if(!proc.insert(v_r.second).second) {
			return shortest_path(s, t, dist, dist_r);
		}
	}

	return -1;
}

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
	for (int i=0; i< t; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		printf("%lld\n", bidijkstra(u-1, v-1));
	}
}
