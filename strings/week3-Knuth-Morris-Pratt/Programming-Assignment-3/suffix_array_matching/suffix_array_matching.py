"""
Algorithm for pattern matching using suffix array:

PatternMatchingWithSuffixArray(Text, Pattern, SuffixArray)
    minIndex = 0
    maxIndex = |Text|

    # find the beginning
    while minIndex < maxIndex
        midIndex = (minIndex + maxIndex)/2

        if Pattern > suffix of text starting at position SuffixArray(midIndex)
            midIndex = midIndex + 1
        else
            maxIndex = midIndex

    start = minIndex
    maxIndex = |Text|

    # find the end
    while minIndex  < maxIndex
        midIndex = (minIndex + maxIndex)/2
        if Pattern < suffix of text starting at position SuffixArray(midIndex)
            maxIndex = midIndex
        else
            minIndex = midIndex + 1

    end  = maxIndex

    if start > end
        return "not found"
    else
        return (start, end)


Uses binary search to find beginning and end of the text in suffix array.
"""

import sys


charmap = {
    "$": 0,
    "A": 1,
    "C": 2,
    "G": 3,
    "T": 4
}


class SuffixTree:
    def __init__(self, text):
        self.textn = list(map(charmap.get, text))
        self.text = text
        self.n = len(text)

    def _sort_characters(self):
        m = max(self.textn)
        order = [0] * self.n
        count = [0] * (m + 1)

        for i in self.textn:
            count[i] = count[i] + 1

        for i in range(1, m + 1):
            count[i] = count[i] + count[i - 1]

        for i in range(len(self.textn) - 1, -1, -1):
            c = self.textn[i]
            count[c] = count[c] - 1
            order[count[c]] = i

        return order

    def _compute_char_classes(self, order):
        classes = [0] * self.n
        classes[order[0]] = 0

        for i in range(1, self.n):
            if self.text[order[i]] != self.text[order[i - 1]]:
                classes[order[i]] = classes[order[i - 1]] + 1
            else:
                classes[order[i]] = classes[order[i - 1]]

        return classes

    def _sort_doubled(self, l, order, classes):
        count = [0] * self.n
        new_order = [0] * self.n

        for i in classes:
            count[i] = count[i] + 1

        for j in range(1, self.n):
            count[j] = count[j] + count[j - 1]

        for i in range(self.n - 1, -1, -1):
            start = (order[i] - l + self.n) % self.n
            cl = classes[start]
            count[cl] = count[cl] - 1
            new_order[count[cl]] = start

        return new_order

    def _update_classes(self, l, order, classes):
        new_classes = [0] * len(order)
        new_classes[order[0]] = 0

        for i in range(1, len(order)):
            cur = order[i]
            prev = order[i - 1]

            mid = (cur + l) % len(order)
            mid_prev = (prev + l) % len(order)

            if classes[cur] != classes[prev] or classes[mid] != classes[mid_prev]:
                new_classes[cur] = new_classes[prev] + 1
            else:
                new_classes[cur] = new_classes[prev]

        return new_classes

    def do(self):
        order = self._sort_characters()
        classes = self._compute_char_classes(order)

        l = 1
        while l < self.n:
            order = self._sort_doubled(l, order, classes)
            classes = self._update_classes(l, order, classes)
            l = 2 * l

        return order


def build_suffix_array(t):
    st = SuffixTree(t)
    return st.do()


def search(text, pattern, suffix_array):
    min_index = 0
    max_index = len(text)

    while min_index < max_index:
        mid_index = int((min_index + max_index) / 2)

        if pattern > text[suffix_array[mid_index]:][:len(pattern)]:
            min_index = mid_index + 1
        else:
            max_index = mid_index

    start = min_index
    max_index = len(text)

    while min_index < max_index:
        mid_index = int((min_index + max_index) / 2)

        if pattern < text[suffix_array[mid_index]:][:len(pattern)]:
            max_index = mid_index
        else:
            min_index = mid_index + 1

    end = max_index

    # print(start, end)
    if start > end:
        return None
    else:
        return [start, end]


if __name__ == '__main__':
    text = sys.stdin.readline().strip()
    suffix_array = build_suffix_array(text)

    sys.stdin.readline()

    patterns = sys.stdin.readline().strip().split(" ")

    results = set()

    for p in patterns:
        res = search(text, p, suffix_array)
        if res is None:
            continue

        for i in range(res[0], res[1]):
            results.add(suffix_array[i])

    print(" ".join(map(str, results)))
