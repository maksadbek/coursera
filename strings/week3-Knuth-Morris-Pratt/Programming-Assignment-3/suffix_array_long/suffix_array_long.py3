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


if __name__ == '__main__':
    text = sys.stdin.readline().strip()
    print(" ".join(map(str, build_suffix_array(text))))
