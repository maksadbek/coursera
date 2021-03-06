#include <iostream>
#include <vector>

using std::vector;

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

int number_of_components(vector<vector<int>> &adj) {
  pre.resize(adj.size());
  post.resize(adj.size());
  visited.resize(adj.size());

  int component_count = 0;
  for(int v = 0; v < adj.size(); v++) {
    if(!visited[v]) {
      dfs(adj, v);
      component_count++;
    }
  }
  
  // for(int v = 0; v < adj.size(); v++) {
  //   std::cout << v << " " << pre[v] << "/" << post[v] << std::endl;
  // }
  
  return component_count;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
