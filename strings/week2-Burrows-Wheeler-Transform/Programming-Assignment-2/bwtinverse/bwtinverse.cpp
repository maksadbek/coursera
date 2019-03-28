#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

void print_set(set<pair<char, int>> s) {
	cout << "set:" << endl;
	for(auto i : s) {
		cout << i.first <<" " << i.second << endl;
	}
}

struct Entry {
	char ch;
	int i;
};

int letter_to_index(char ch) {
	switch (ch)
	{
		case '$':
			return 0;
		case 'A':
			return 1;
		case 'C':
			return 2;
		case 'G':
			return 3;	
		case 'T':
			return 4;
		default:
			return -1;
	}
};

inline vector<Entry> sort(const string& bwt) {
	int max_value = 5;
	vector<Entry> entries(bwt.size());
	vector<int> count(max_value, 0);

	for(int i = 0; i < bwt.size(); i++) {
		count[letter_to_index(bwt[i])]++;
	}

	for(int i = 1; i < max_value; i++) {
		count[i] += count[i-1];
	}

	for(int i = bwt.size()-1; i >= 0; i--) {
		entries[count[letter_to_index(bwt[i])]-1] = Entry{.ch = bwt[i], .i = i};
		count[letter_to_index(bwt[i])] -= 1;
	}

	return entries;
}

string InverseBWT(const string& bwt) {
	string text = "";
	auto entries = sort(bwt);
	
	int i;
	for(i = 0; i < bwt.size(); i++) {
		if(bwt[i] == '$') {
			break;
		}
		// printf("%c %d\n", bwt[i], i);
	}

	char sym;
	do {
		auto entry = entries[i];
		sym = entry.ch;
		text.push_back(sym);
		i = entry.i;
		// printf(">>> sym: %c \n", sym);
	} while(sym != '$');

	return text;
}

int main() {
	string bwt;
	cin >> bwt;
	cout << InverseBWT(bwt) << endl;
	return 0;
}
