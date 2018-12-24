#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::make_pair;
using std::string;
using std::to_string;
using std::numeric_limits;

const int max_int = numeric_limits<int>::max();

vector<string> shortest_paths(vector<vector<pair<int,int>>> &adj, int s) {
	vector<long long> dist(adj.size(), max_int);
	dist[s] = 0;

	for(int i = 0; i < adj.size()-1; i++) {
		for(int u = 0; u < adj.size(); u++) {
			for(auto v : adj[u]) {
				int to = v.first;
				int w = v.second;

				if(dist[u] != max_int && dist[u] + w < dist[to]) {
					dist[to] = dist[u] + w;
				}
			}
		}
	}

	vector<string> result(adj.size());
	result[s] = "0";

	queue<int> q;
        for(int i = 0; i < 1; i++) {
		for(int u = 0; u < adj.size(); u++) {
			for(auto v : adj[u]) {
				int to = v.first;
				int w = v.second;

				if(dist[u] != max_int && dist[u] + w < dist[to]) {
					dist[to] = dist[u] + w;
					q.push(to);
				}
			}
		}
        }

	vector<int> neg;
	vector<bool> used(adj.size(), false);
	
	// do a bfs and find vertexes of negative cycles
	while(!q.empty()) {
	  int u = q.front();
	  q.pop();
	  
	  if(used[u]) {
	    continue;
	  }

	  used[u] = true;
	  neg.push_back(u);
	  
	  for(auto v : adj[u]) {
	    if(!used[v.first]) {
	      q.push(v.first);
	    }
	  }
	}

        for(int i = 0; i < dist.size(); i++) {
                if(dist[i] == max_int) {
                        result[i] = "*";
			continue;
                }

		bool negative = false;
		for(int x : neg) {
		  if(x == i) {
		    negative = true;
		    break;
		  }
		}

		if(negative) {
		  result[i] = "-";
		  continue;
		}

		result[i] = to_string(dist[i]);
        }

	return result;
}

int main() {
	int n, m, s;
	std::cin >> n >> m;

	vector<vector<pair<int,int>>> adj(n, vector<pair<int,int>>());

	for (int i = 0; i < m; i++) {
		int x, y, w;
		std::cin >> x >> y >> w;

		adj[x - 1].push_back(make_pair(y - 1, w));
	}

	std::cin >> s;

	auto result = shortest_paths(adj, s-1);
	for (auto x : result ) {
		std::cout << x << "\n";
	}
}
