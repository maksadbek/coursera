#include <iostream>
#include <vector>

using std::vector;

class DisjSet {
public:
	explicit DisjSet(int n) {
		s = vector<int>(n, -1);
	};

	int find(int x) const {
		return find(x);
	};
	
	int find(int x) {
		if(s[x] < 0) {
			return x;
		} else {
			return find(s[x]);
		}
	};
	
	void union_sets(int root1, int root2) {
		s[root2] = root1;
	};
	
private:
	vector<int> s;
};

int main() {
	printf("hello!\n");
	DisjSet set(10);

	set.union_sets(1, 2);

	printf("%d %d\n", set.find(1), set.find(2));
	
}


	
	
