#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::queue;
using std::reverse;
using std::cout;

struct BFS {
	BFS(vector<vector<int>> a) {
		adj = a;
		d.resize(adj.size());
		used.resize(adj.size());
		path.resize(adj.size());
	};

	void run(int s) {
		d[s] = 0;
		q.push(s);
                used[s] = true;
                path[s] = -1;

                while(!q.empty()) {
	                int u = q.front();
	                q.pop();

	                for (int i = 0; i < adj[u].size(); i++) {
		                int to = adj[u][i];
				if (!used[to]) {
					used[to] = true;
					d[to] = d[u] + 1;
					q.push(to);
					path[to] = u;
		                }
	                }
                }
	}

	int distance(int to) {
		if(!used[to]) {
			return -1;
		}

		vector<int> p;
		for(int v = to; v != -1; v=path[v]) {
			p.push_back(v);
		}

		return p.size()-1;

		/*
		reverse(p.begin(), p.end());

		cout << "path: ";
		for(size_t i = 0; i < p.size(); i++) {
			cout << p[i] + 1 << " ";
		}
		*/

	}

private:
    queue<int> q;
    vector<bool> used;
    vector<int> d;
    vector<int> path;
    vector<vector<int>> adj;
};


int distance(vector<vector<int> > &adj, int s, int t) {
	BFS bfs(adj);

	bfs.run(s);
	return bfs.distance(t);
}

void pprint(int a, b) {
	printf("sum is: ", a + b);
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
