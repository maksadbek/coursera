# python3
import sys


def compute_prefix(p):
    s = [0] * (len(p))
    border = 0
    for i in range(1, len(p)):
        while border > 0 and p[i] != p[border]:
            border = s[border-1]
        
        if p[i] == p[border]:
            border += 1
        else:
            border = 0
        
        s[i] = border
    
    return s


def kmp(p, s):
    text = p + "$" + s
    prefix = compute_prefix(text)
    result = []
    
    for i in range(len(p) + 1, len(text)):
        if prefix[i] == len(p):
            result.append(i - 2*len(p))
    
    return result


if __name__ == '__main__':
    pattern = sys.stdin.readline().strip()
    t = sys.stdin.readline().strip()
    r = kmp(pattern, t)
    print(" ".join(map(str, r)))

