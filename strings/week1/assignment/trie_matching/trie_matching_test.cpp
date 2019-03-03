#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <map>
#include <chrono>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

default_random_engine gen;
uniform_int_distribution<int> dist(0, 3);

struct Node {
	int next[Letters];

	Node() {
		fill(next, next + Letters, NA);
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

char index_to_letter(int i) {
  switch(i) {
  case 0: return 'A'; break;
  case 1: return 'C'; break;
  case 2: return 'G'; break;
  case 3: return 'T'; break;
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
  }

  return t;
}

vector<int> slow(const string & text, const vector<string> & patterns) {
  vector<int> result;

  for(auto pattern : patterns) {
    for(int i = 0; i < text.size(); i++) {
      if(text.substr(i, pattern.size()) == pattern) {
	result.push_back(i);
      }
    }
  }

  return result;
}

string rand_text(int size) {
  string text;

  for(int i = 0; i < size; i++) {
    text.push_back(index_to_letter(dist(gen)));
  }

  return text;
}

int match_prefix(const string & text, int s, trie t) {
  int prefix = -1;
  char sym = text[s];
  Node v = t[0];

  while(true) {
    if(v.is_leaf()) {
      return prefix;
    }

    if(sym == '\0') {
      return -1;
    }

    int next = v.next[letter_to_index(sym)];
    if(next != NA) {
      if(prefix < 0) {
	prefix = next;
      }

      v = t[next];
      sym = text[++s];

      continue;
    }

    return -1;
  }

  return prefix;
}

void print_trie_g(trie t) {
  printf("trie:");
  for(int i = 0; i < t.size(); i++) {
    for(int j = 0; j < 4; j++) {
      if(t[i].next[j] != NA) {
        printf("%d -> %d [label=%c];\n", i, t[i].next[j], index_to_letter(j));
      }
    }
  }
  printf("<<<<<<<<\n");
}

void print_trie(trie t) {
  printf("trie:");
  for(int i = 0; i < t.size(); i++) {
    for(int j = 0; j < 4; j++) {
      if(t[i].next[j] != NA) {
	printf("%d -> %d; %c\n", i, t[i].next[j], index_to_letter(j));
      }
    }
  }
  printf("<<<<<<<<\n");
}

vector <int> solve (const string& text, int n, const vector <string>& patterns) {
  vector <int> result;

  trie t = build_trie(patterns);
  for(int i = 0; i < text.size(); i++) {
    int p = match_prefix(text, i, t);
    if(0 < p) {
      result.push_back(i);
    }
  }

  return result;
}

vector<int> solve_with_slow(const string& text, const vector<string>& patterns) {
  return slow(text, patterns);
}

string aaa_text(int n) {
  string result;
  for(int i = 0; i < n; i++) {
    result.push_back('A');
  }

  return result;
}

int main (void) {
  for(int i = 0; i < 100; i++) {
    string t = rand_text(10000);

    int n = 5000;

    vector <string> patterns (n);
    for (int i = 0; i < n; i++) {
      patterns[i] = rand_text(100);
    }

    vector <int> ans;
    using clock = chrono::steady_clock;
    
    clock::time_point start = clock::now();
    ans = solve (t, n, patterns);
    clock::time_point end = clock::now();
    clock::duration execution_time = end - start;
    
    cout << "time: " << chrono::duration_cast<std::chrono::milliseconds>(execution_time).count() << "ms"<< endl;

    auto slow_ans = solve_with_slow(t, patterns);
    if(ans == slow_ans) {
      cout << "test #" << i << " is ok" << endl;
    } else {
      cout << "text:" << t << endl;
      cout << "patterns:" << endl;

      auto ttt = build_trie(patterns);
      print_trie_g(ttt);

      for(auto p : patterns) {
	cout << p << endl;
      }
      cout << endl;

      cout << "ans:" << endl;

      for (int i = 0; i < (int) ans.size (); i++) {
	cout << ans[i];
	if (i + 1 < (int) ans.size ()) {
	  cout << " ";
	} else {
	  cout << endl;
	}
      }
      
      cout << "slow_ans:" << endl;
      for (int i = 0; i < (int) slow_ans.size (); i++) {
        cout << slow_ans[i];
        if (i + 1 < (int) slow_ans.size ()) {
          cout << " ";
        } else {
          cout << endl;
        }
      }

      return 0;
    }
  }

  return 0;
}
