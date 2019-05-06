#include <algorithm>
#include <iostream>
#include <limits>
#include <stack>
#include <vector>
#include <queue>

using std::min;
using std::numeric_limits;
using std::stack;
using std::vector;
using std::queue;

struct Edge {
  int from, to, capacity, flow;
};

class FlowGraph {
private:
  vector<Edge> edges;
  vector<vector<size_t>> graph;

public:
  explicit FlowGraph(size_t n) : graph(n) {}

  // We first append a forward edge and then a backward edge.
  // All forward edges are stored at EVEN indices (starting from 0),
  // whereas backward edges are stored at ODD indices in the list edges.
  void add_edge(int from, int to, int capacity) {
    Edge forward_edge = {from, to, capacity, 0};
    Edge backward_edge = {to, from, 0, 0};

    graph[from].push_back(edges.size());
    edges.push_back(forward_edge);

    graph[to].push_back(edges.size());
    edges.push_back(backward_edge);
  }

  size_t size() const { return graph.size(); }

  const vector<size_t> &get_ids(int from) const {
    return graph[from];
  }

  const Edge &get_edge(size_t id) const {
    return edges[id];
  }

  // To get a backward edge for a true forward edge (i.e id is even).
  // We should get id + 1 due to the described above scheme.
  // On the other hand, when we have to get a "backward" edge for a backward edge
  // i.e. get a forward edge for backward - id is odd, id - 1 should be taken.
  // It turns out that id ^ 1 works for both cases. Think this through!
  void add_flow(size_t id, int flow) {
    edges[id].flow += flow;
    edges[id ^ 1].flow -= flow;
  }
};

FlowGraph read_data() {
  int vertex_count, edge_count;
  std::cin >> vertex_count >> edge_count;
  FlowGraph graph(vertex_count);
  for (int i = 0; i < edge_count; ++i) {
    int u, v, capacity;
    std::cin >> u >> v >> capacity;
    graph.add_edge(u - 1, v - 1, capacity);
  }
  return graph;
}

vector<int> bfs(FlowGraph &graph, int from, int to) {
  queue<int> q;
  q.push(from);
  vector<bool> used(graph.size());
  vector<int> parent(graph.size(), -1);

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    used[u] = true;

    if(u == to) {
    	break;
    }

    for(auto v : graph.get_ids(u)) {
      const Edge& edge = graph.get_edge(v);
      if ((edge.capacity - edge.flow) <= 0) {
        printf("invalid edge(%d): %d -> %d = %d\n", v, edge.from+1, edge.to+1, edge.capacity - edge.flow);
        continue;
      }

      if(!used[edge.to]) {
      	q.push(edge.to);
        parent[edge.to] = v;
      }
    }
  }


  vector<int> path;
  while(to != from) {
    auto id = parent[to];
    if(id == -1) {
      return vector<int>();
    }
    path.push_back(id);
    to = graph.get_edge(id).from;
  }

  return path;
}

int max_flow(FlowGraph &graph, int from, int to) {
  int flow = 0;

  while (true) {
    auto path = bfs(graph, from, to);
    if (path.empty()) {
      break;
    }

    int cf = numeric_limits<int>::max();

    printf("shortest path:");
    for (auto &edge_id: path) {
      auto edge = graph.get_edge(edge_id);
      printf("%d -> %d(%d), ", edge.from+1, edge.to+1, edge.capacity-edge.flow);
      cf = min(cf, edge.capacity - edge.flow);
    }
    printf("\n");
    printf("min: %d\n", cf);

    flow += cf;

    for (auto &edge : path) {
      graph.add_flow(edge, cf);
    }

  }

  return flow;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  FlowGraph graph = read_data();

  std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
  return 0;
}
