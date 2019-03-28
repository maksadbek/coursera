#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  t.resize(1, edges());

  int counter = 0;
  for(const auto & p : patterns) {
    size_t current_node = 0;

    for(size_t i = 0; i < p.size(); i++) {
      char current_sym = p[i];
      bool node_exists = false;

      for(const auto &n : t[current_node]) {
	 if(n.first == current_sym) {
	      current_node = n.second;
	      node_exists = true;
	      break;
	 }
      }
      
      if(!node_exists) {
        t[current_node].emplace(current_sym, ++counter);
        current_node = counter;
	t.resize(counter+1);
      }
    }
  }

  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}
