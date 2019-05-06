#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

class charts {
public:
  int n, m;
  vector<bool> visited;
  vector<int> assign;
  vector<vector<bool>> g;

  void solve() {
    read_data();
    int result = min_charts();
    cout << result << "\n";
  }

private:
  void read_data() {
    cin >> n >> m;

    visited.resize(n, false);
    assign.resize(n, -1);

    vector<vector<int>> stocks(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> stocks[i][j];
      }
    }

    g.resize(n, vector<bool>(n));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        g[i][j] = cmp(stocks[i], stocks[j]);
      }
    }
  }

  int min_charts() {
    int count = 0;
    for (int i = 0; i < n; i++) {
      fill(visited.begin(), visited.end(), false);

      if (match(i)) {
        count++;
      }
    }

    return n - count;
  }

  bool match(int u) {
    if (u == -1) {
      return true;
    }

    if (visited[u]) {
      return false;
    }

    visited[u] = true;

    for (int v = 0; v < n; v++) {
      // the charts must be strictly below.
      if (g[u][v] and match(assign[v])) {
        assign[v] = u;
        return true;
      }
    }

    return false;
  }

  bool cmp(const vector<int> &stock1, const vector<int> &stock2) {
    for (int i = 0; i < stock1.size(); i++) {
      if (stock1[i] >= stock2[i]) {
        return false;
      }
    }

    return true;
  }
};

int main() {
  charts ch;
  ch.solve();

  return 0;
}
