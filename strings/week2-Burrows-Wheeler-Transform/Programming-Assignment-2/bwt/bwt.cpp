#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

string BWT(const string& text) {
	string result = "";
	vector<string> m(text.size());

	m[0] = text;
	auto last = m[0].back();
	m[0].pop_back();
	m[0].insert(m[0].begin(), last);

	for(size_t i = 1; i < text.size(); i++) {
		m[i] = m[i-1];
		auto last = m[i].back();
		m[i].pop_back();
		m[i].insert(m[i].begin(), last);
	}

	sort(m.begin(), m.end());

	for(size_t i = 0; i < m.size(); i++) {
		result.push_back(m[i].back());
	}

	return result;
}

int main() {
	string text;
	cin >> text;
	cout << BWT(text) << endl;
	return 0;
}