#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::pair;

vector<bool> used;
vector<int> order;

void dfs(vector<vector<int>> &adj, int s) {
	used[s] = true;

	for(int i = 0; i < adj[s].size(); i++) {
		int to = adj[s][i];

		if(!used[to]) {
			dfs(adj, to);
		}
	}

	order.push_back(s);

        return;
}

vector<int> backtrace;
vector<bool> visited;

bool is_acyclic(vector<vector<int>> &adj, int s) {
	visited[s] = true;
	backtrace.push_back(s);

	for(int i = 0; i < adj[s].size(); i++) {
		int to = adj[s][i];

		for(auto x: backtrace) {
			if(to==x) {
				return 1;
			}
		}

		if(!visited[to]) {
			if(is_acyclic(adj, to)) {
				return true;
			}
		}
	}

	backtrace.pop_back();

	return false;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  used.resize(n, false);

  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }

  for(int i = 0; i < adj.size(); i++) {
  	if(!used[i]) {
	        dfs(adj, i);
  	}
  }

  std::reverse(order.begin(), order.end());

  visited.resize(n, false);
  for(auto x : order) {
  	if(!visited[x]) {
	        if(is_acyclic(adj, x)) {
		        std::cout << 1;
		        return 0;
	        }
  	}
  }

  std::cout << 0;
}
