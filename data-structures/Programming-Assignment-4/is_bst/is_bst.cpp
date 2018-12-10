#include <algorithm>
#include <iostream>
#include <vector>

#include "death_handler.h"


using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::is_sorted;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

vector<int> traversal;

bool post_order(const vector<Node> &tree, int root) {
  if(root == -1) {
    return true;
  }

  auto node = tree[root];

  if(!post_order(tree, node.left)) {
          return false;
  }

  if(node.left != -1 and tree[node.left].key >= node.key) {
          return false;
  }

  traversal.push_back(node.key);

  if(!post_order(tree, node.right-1)) {
          return false;
  }
    
  return true;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  if(tree.size() == 0) {
    return true;
  }
  
  if(!post_order(tree, 0)){
          return false;
  }

  return is_sorted(traversal.begin(), traversal.end());
}

int main() {
  Debug::DeathHandler dh;

  int nodes;
  cin >> nodes;
  vector<Node> tree;
  tree[10];
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
