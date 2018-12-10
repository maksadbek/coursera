#include <iostream>
#include <vector>

using std::vector;
using std::pair;

vector<int> pre;
vector<int> post;
vector<bool> visited;

int i = 1;

void dfs(vector<vector<int>> &adj, int x) {
  if(!visited[x]) {
    visited[x] = true;
  }
  
  pre[x] = i++;

  for(auto child: adj[x]) {
    if(visited[child]) {
      continue;
    }
      
    visited[child] = true;

    dfs(adj, child);
  }

  post[x] = i++;
}

int reach(vector<vector<int>> &adj, int x, int y) {
  pre.resize(adj.size());
  post.resize(adj.size());
  visited.resize(adj.size());

  for(int v = 0; v < adj.size(); v++) {
    if(!visited[v]) {
      dfs(adj, v);
    }
  }
  
  for(int v = 0; v < adj.size(); v++) {
    std::cout << v << " " << pre[v] << "/" << post[v] << std::endl;
  }
  
  if(pre[x] < pre[y] && post[y] < post[x]) {
    return 1;
  }
  
  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int>> adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
