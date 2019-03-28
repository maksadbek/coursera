#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <iostream>
#include <memory>
#include <cassert>

using namespace std;

class Graph {
	typedef int Distance;
	typedef int Vertex;

	// Number of nodes
	size_t N;

	// Source and target
	int s, t;

	// Estimate of the distance from s to t
	int estimate = INFINITY;

	// Lists of edges outgoing from each node
	vector<vector<pair<int, int>>> outgoing_edges;

	// Lists of edges incoming to each node
	vector<vector<pair<int, int>>> incoming_edges;

	static constexpr int INFINITY = std::numeric_limits<int>::max() / 2;

	// Levels of nodes for node ordering
	vector<int> level;

	// Ranks of nodes - positions in the node ordering
	vector<int> rank;

	// Distance to node v, bidistance[0][v] - from source in the forward search, bidistance[1][v] - from target
	// in the backward search.
	vector<vector<Distance>> bidistance;

	vector<int> distance;

	// Wrapper around STL priority_queue
	class StlHeap {
	public:
		using T = pair<Distance, Vertex>;
		using Queue = priority_queue<T, vector<T>, greater<>>;

		StlHeap() {
			queue = Queue();
		}

		bool empty() const {
			return queue.empty();
		}

		void update(Vertex v, Distance d) {
			queue.push(std::make_pair(d,v));
		}

		void clear() {
			queue = Queue();
		}

		std::pair<Distance, Vertex> pop() {
			pair<Distance, Vertex> top = queue.top();
			queue.pop();
			return top;
		}

	private:
		Queue queue;
	};

	// Priority queues for forward and backward searches
	StlHeap diqueue[2];
public:
	Graph(size_t N, int s, int t) : N(N), s(s), t(t) {
		read_stdin();
		bidistance.resize(2, std::vector<int>(N, INFINITY));
	}

	size_t get_n() {
		return N;
	}

	std::vector<std::pair<int, int>>& get_adjacent(int v, bool forward = true) {
		if (forward) {
			return outgoing_edges[v];
		}

		return incoming_edges[v];
	}

	void preprocess() {
		distance.resize(N, INFINITY);
		// Priority queue will store pairs of (importance, node) with the least important node in the head
		std::priority_queue<std::pair<int, int>, std::vector<std::pair<int,int>>, greater<>> queue;

		// Implement the rest of the algorithm yourself
	}

	// Returns distance from s to t in the graph
	int query(int u, int w) {
		update(u, 0, true);
		update(w, 0, false);
		s = u;
		t = w;
		// Implement the rest of the algorithm yourself

		return -1;
	}

private:
	// Try to relax the node v using distance d either in the forward or in the backward search
	void update(int v, int d, bool forward) {
		// Implement this method yourself
	}

	class VertexSet {
	public:
		explicit VertexSet(size_t n = 0) : visited(n) {}

		void resize(size_t n) {
			visited.resize(n);
		}

		void add(int v) {
			if (!visited[v]) {
				vertices.push_back(v);
				visited[v] = true;
			}
		}

		const std::vector<int>& get() const {
			return vertices;
		}

		const bool has(int v) {
			return bool(visited[v]);
		}

		void clear() {
			for (int v : vertices) {
				visited[v] = false;
			}
			vertices.clear();
		}

	private:
		std::vector<int> visited;
		std::vector<int> vertices;
	};

	VertexSet visited;

	// QEntry = (distance, vertex)
	typedef std::pair<int,int> QEntry;
	std::priority_queue<QEntry, std::vector<QEntry>, greater<>> queue;

	struct Shortcut {
		int from;
		int to;
		int cost;
	};

	// Adds all the shortcuts for the case when node v is contracted, and returns the importance of node v
	// in this case
	int do_shortcut(int v, std::vector<Shortcut>& shortcuts, int& mylevel) {
		// Implement this method yourself

		// Add neighbors and shortcut cover heuristics
		return (shortcuts.size() - outgoing_edges[v].size() - incoming_edges[v].size()) + mylevel;
	}

	void set_n(size_t n) {
		N = n;
		outgoing_edges.resize(n);
		incoming_edges.resize(n);
	}


	void add_edge_to_list(std::vector<std::pair<int,int>>& list, int w, int c) {
		for (auto &p : list) {
			if (p.first == w) {
				if (p.second > c) {
					p.second = c;
				}
				return;
			}
		}

		list.push_back(w, c);
	}

	void add_directed_edge(int u, int v, int c) {
		add_edge_to_list(outgoing_edges[u], v, c);
		add_edge_to_list(incoming_edges[v], u, c);
	}

	void add_edge(int u, int v, int c) {
		add_directed_edge(u, v, c);
	}

	void finalize() {
		// Remove unnecessary edges
	}

	bool read_stdin() {
		int u,v,c,n,m;
		assert(scanf("%d %d", &n, &m) == 2);
		set_n(n);
		for (int i = 0; i < m; ++i) {
			assert(scanf("%d %d %d", &u, &v, &c) == 3);
			add_edge(u-1, v-1, c);
		}
		finalize();
		return true;
	}
};

int main() {
	Graph g;
	g.preprocess();
	std::cout << "Ready" << std::endl;

	int t;
	assert(scanf("%d", &t) == 1);
	for (int i = 0; i < t; ++i) {
		int u, v;
		assert(scanf("%d %d", &u, &v) == 2);
		printf("%d\n", g.query(u-1, v-1, 3));
	}
}
