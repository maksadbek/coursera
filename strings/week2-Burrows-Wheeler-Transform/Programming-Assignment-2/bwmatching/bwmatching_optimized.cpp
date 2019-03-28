/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string letters = "ACGT$";

void print_vec(vector<int> v) {
	for(int i = 0; i < v.size(); i++) {
		printf("%d %d\n", i, v[i]);
	}
}

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

inline string count_sort(const string& bwt) {
	int max_value = 5;
	string entries;
	entries.resize(bwt.size());

	vector<int> count(max_value, 0);

	for(int i = 0; i < bwt.size(); i++) {
		count[letter_to_index(bwt[i])]++;
	}

	for(int i = 1; i < max_value; i++) {
		count[i] += count[i-1];
	}

	for(int i = bwt.size()-1; i >= 0; i--) {
		entries[count[letter_to_index(bwt[i])]-1] = bwt[i];
		count[letter_to_index(bwt[i])] -= 1;
	}

	return entries;
}

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
// * starts - for each character C in bwt, starts[C] is the first position
//   of this character in the sorted array of
//   all characters of the text.
// * occ_count_before - for each character C in bwt and each position P in bwt,
//   occ_count_before[C][P] is the number of occurrences of character C in bwt
//   from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt, vector<int>& starts, map<char, vector<int>>& occurences) {
	for(char l : letters) {
		occurences.emplace(l, vector<int>(bwt.size()+1, 0));
	}

	for(size_t i = 1; i <= bwt.size(); i++) {
		for(char ch : letters) {
			occurences.find(ch)->second[i] = occurences.find(ch)->second[i-1];
			if(ch == bwt[i-1]) {
				occurences.find(ch)->second[i]++;
			}
		}
	}

	auto sorted = count_sort(bwt);
	// cout << "sorted: " << sorted << endl;
	for(size_t i = 0; i < sorted.size(); i++) {
		if(starts[letter_to_index(sorted[i])] < 0) {
			starts[letter_to_index(sorted[i])]= i;
		}
	}

/*
	for(size_t i = 0; i < starts.size(); i++) {
		printf("starts: %zu %d\n", i, starts[i]);
	}

	for(size_t i = 0; i <= bwt.size(); i++) {
		printf("level: %zu:\n", i);
		for(char l : letters) {
			printf("%c: %d, ", l, occurences.find(l)->second[i]);
		}
		printf("\n");
	}
*/
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern,
                     const string& bwt,
                     const vector<int>& starts,
                     const map<char, vector<int>>& occurences) {
	int top = 0;
	int bottom = bwt.size() - 1;
	int p = pattern.size() - 1;

	while(top <= bottom) {
		if(p < 0) {
			break;
		}

		char ch = pattern[p];
		// printf("search: %c\n", ch);
		// printf("top: %d, bottom: %d\n", top, bottom);

		bool contains = false;

		for(int i = top; i <= bottom; i++) {
			if(bwt[i] == ch) {
				contains = true;
				break;
			}
		}

		// printf("contains ? %d\n", contains);
		auto occ = occurences.find(ch)->second;
		top = starts[letter_to_index(ch)] + occ[top];
		bottom = starts[letter_to_index(ch)] + occ[bottom+1]-1;
		p--;
	}

	return bottom-top+1;
}


int main() {
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;
  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  vector<int> starts(5, -1);

  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, vector<int> > occ_count_before;

  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);

  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}
