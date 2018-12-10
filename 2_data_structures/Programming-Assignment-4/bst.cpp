#include <iostream>


template <typename Comparable>
class BinarySearchTree {
        public:
               BinarySearchTree();
               BinarySearchTree(const BinarySearchTree &tree);
               BinarySearchTree(BinarySearchTree &&tree); 
               ~BinarySearchTree();

               const Comparable & find_min() const;
               const Comparable & find_max() const;
               bool contains(const Comparable & x) const;
               bool is_empty() const;
               void print(ostream & out = cout) const;

               void make_empty();
               void insert(const Comparable & x);
               void insert(Comparable & x);
               void remove(const Comparable & x);

               BinarySearchTree & operator=(const BinarySearchTree & tree);
               BinarySearchTree & operator=(BinarySearchTree && tree);
        
        private:
                struct BinaryNode {
                        Comparable element;
                        BinaryNode *left;
                        BinaryNode *right;

                        BinaryNode(const Comparable & element, BinaryNode * lt, BinaryNode * rt) {
                                element = element;
                                left = lt;
                                right = rt;
                        }

                        BinaryNode(Comparable & element, BinaryNode * lt, BinaryNode * rt) {
                                element = element;
                                left = lt;
                                right = rt;
                        }
                };

                BinaryNode *root;

                // insert creates a new node in the tree.
                void insert(const Comparable & x, BinaryNode * & t) {
                        
                };

                void insert(Comparable && x, BinaryNode * & t);

                void remove(const Comparable & x, BinaryNode * & t);


                // find_min returns the min elemetn in the tree.
                BinaryNode * find_min(BinaryNode *t) const {
                        while(t->left != nullptr) {
                                t = t->left;
                        }

                        return t;
                };

                // find_max returns the max element in the tree.
                BinaryNode * find_max(BinaryNode *t) const;

                // contains tests if an item is in a subtree.
                bool contains(const Comparable & x, BinaryNode * t) const {
                        if(t == nullptr) {
                                return false;
                        } else if (x  < t->element) {
                                return contains(x, t->left);
                        } else if (t->element < x) {
                                return contains(x, t->right);
                        }

                        return true;
                };

                // make_empty removes all nodes from the tree.
                void make_empty(BinaryNode * & t);

                // print prints the tree to the given stream.
                void print(BinaryNode * t, ostream & out) const;

                // clone returns the copy of the tree.
                BinaryNode * clone(BinaryNode * t) const;
};

int main() {
        return 0;
}