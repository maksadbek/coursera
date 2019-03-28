import sys


class SuffixTree:
    def __init__(self, text):
        self.charmap = {"A": 0, "C": 1, "G": 2, "T": 3}
        self.text = text
        self.n = len(text)

    def _sort_characters(self):
        order = [0] * self.n
        count = dict()

        for t in text:
            count[t] = count[t] + 1

        for i in "ACGT":
            count[i] = count[i] + count[self.charmap[i]-1]

        for i in range(len(text), -1, -1):
            count[text[i]] = count[text[i]] - 1
            order[count[text[i]]] = i

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

        for i in range(0, self.n):
            count[classes[i]] = count[classes[i]] + 1

        for j in range(1, self.n):
            count[j] = count[j] + count[j] - 1

        for i in range(self.n - 1, -1, -1):
            start = (order[i] - l + self.n) % self.n
            cl = classes[start]
            count[cl] = count[cl] - 1
            new_order[count[cl]] = start

        return new_order

if __name__ == '__main__':
    text = sys.stdin.readline().strip()
    print(" ".join(map(str, build_suffix_array(text))))
