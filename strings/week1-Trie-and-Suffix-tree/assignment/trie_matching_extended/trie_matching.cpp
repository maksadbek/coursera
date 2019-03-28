#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <map>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

default_random_engine gen;
uniform_int_distribution<int> dist(0, 3);

struct Node {
	int next[Letters];
        bool pattern;

	Node() {
		fill(next, next + Letters, NA);
                pattern = false;
	}

	bool is_leaf() const {
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

typedef vector<Node> trie;

void fill(int next[], int n, int v) {
  for(int i = 0; i < n; i++) {
    next[i] = v;
  }
}

int letter_to_index(char letter) {
	switch (letter) {
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

trie build_trie(const vector<string> & patterns) {
  trie t;
  t.resize(1, Node());

  int counter = 0;
  for(const auto & p : patterns) {
    int current_node = 0;

    for(size_t i = 0; i < p.size(); i++) {
      char current_sym = p[i];
      
      int next = t[current_node].next[letter_to_index(current_sym)];
      if(next != NA) {
	current_node = next;
	continue;
      }

      t[current_node].next[letter_to_index(current_sym)] = ++counter;
      t.resize(counter+1, Node());
      current_node = counter;
    }

    t[current_node].pattern = true;
  }

  return t;
}

bool match_prefix(const string & text, int s, const trie& t) {
  int prefix = -1;
  char sym = text[s];
  Node v = t[0];
  bool match_pattern = false;

  while(true) {
    if(v.is_leaf()) {
      return match_pattern;
    }

    if(sym == '\0') {
      return match_pattern;
    }

    int next = v.next[letter_to_index(sym)];
    if(next != NA) {
      if(t[next].pattern) {
        match_pattern = true;
      }

      if(prefix < 0) {
	prefix = next;
      }

      v = t[next];
      sym = text[++s];

      continue;
    }

    return match_pattern;
  }

  return match_pattern;
}

vector <int> solve (const string& text, int n, const vector <string>& patterns) {
  vector <int> result;

  trie t = build_trie(patterns);

  for(int i = 0; i < text.size(); i++) {
    if(match_prefix(text, i, t)) {
      result.push_back(i);
    }
  }

  return result;
}

int main (void) {
  string t;
  cin >> t;

  int n;
  cin >> n;

  vector <string> patterns (n);
  for (int i = 0; i < n; i++) {
    cin >> patterns[i];
  }
  
  vector <int> ans;
  ans = solve (t, n, patterns);

  for (int i = 0; i < (int) ans.size (); i++) {
    cout << ans[i];
    if (i + 1 < (int) ans.size ()) {
      cout << " ";
    } else {
      cout << endl;
    }
  }
  
  return 0;
}
