#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;

vector<bool> used;
vector<int> order;

void toposort(vector<vector<int>> &adj, int s) {
  used[s] = true;

  for(int i = 0; i < adj[s].size(); i++) {
    int to = adj[s][i];

    if(!used[to]) {
      toposort(adj, to);
    }
  }

  order.push_back(s);

  return;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }

  used.resize(n, false);

  for(int i = 0; i < n; i++) {
  	if(!used[i]) {
          toposort(adj, i);
  	}
  }

  reverse(order.begin(), order.end());
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
