#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::queue;

struct Bipartite {
    Bipartite(vector<vector<int>> &adj) : g(adj) {
    	colors.resize(g.size(), 0);
    	used.resize(g.size(), false);
    }

    int bfs(int s) {
	queue<int> q;

        q.push(s);
	colors[s] = white;

	while(!q.empty()) {
		int c = q.front();
		q.pop();
		used[c] = true;

		for(int i = 0; i < g[c].size(); i++) {
			int to = g[c][i];

			printf("v: %d, color: %d, parent: %d, parent_color: %d\n",
			       to, colors[to],
			       c, colors[c]
			);

			if(colors[c] == colors[to]) {
				return 0;
			}

			if(!used[to]) {
				if(colors[c] == white) {
					colors[to] = black;
				} else {
					colors[to] = white;
				}

				q.push(to);
			}
		}
	}

	return 1;
    }

private:
    const vector<vector<int>> &g;
    vector<int> colors;
    vector<bool> used;

    const int white = 1;
    const int black = 2;
};

int bipartite(vector<vector<int>> &adj) {
	Bipartite b(adj);

	return b.bfs(0);
}

int main() {
	int n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	for (int i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		adj[x - 1].push_back(y - 1);
		adj[y - 1].push_back(x - 1);
	}

	std::cout << bipartite(adj);
}
