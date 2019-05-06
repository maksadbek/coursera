#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::stack;
using std::vector;

class MaxMatching {
public:
  void solve() {
    vector<vector<bool>> adj_matrix = read_data();
    find_matching(adj_matrix);

    for(int i : assign_flights) {
      if(i >= 0) {
    	  i += 1;
      }

      cout << i << " ";
    }

    cout << endl;
  }

private:
  int n, m;
  vector<int> assign_crews;
  vector<int> assign_flights;
  vector<vector<bool>> adj_matrix;

  vector<vector<bool>> read_data() {
    cin >> n >> m;

    assign_flights.resize(n, -1);
    assign_crews.resize(m, -1);

    adj_matrix.resize(n, vector<bool>(m));

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        int bit;
        cin >> bit;
        adj_matrix[i][j] = (bit == 1);
      }
    }

    return adj_matrix;
  }

  int find_matching(const vector<vector<bool>> &adj_matrix) {
    int count = 0;

    for(int u = 0; u < n; u++) {
      vector<bool> visited(n, false);

      if(match(u, visited)) {
        count++;
      }
    }

    return count;
  }

  bool match(int u, vector<bool>& visited) {
    if(u == -1) {
    	return true;
    }

    if(visited[u]) {
    	return false;
    }

    visited[u] = true;

    for(int v = 0; v < m; v++) {
      if(adj_matrix[u][v] and match(assign_crews[v], visited)) {
        assign_flights[u] = v;
        assign_crews[v] = u;
        return true;
      }
    }

    return false;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  MaxMatching max_matching;
  max_matching.solve();
  return 0;
}
