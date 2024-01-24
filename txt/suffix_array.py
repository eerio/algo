from itertools import pairwise
s = input()

suffixes = [s[i: ] for i in range(len(s))]
suffixes.sort()

print('Suffix array:')
sa = [len(s) - len(suffix) for suffix in suffixes]
print(sa)


def lcp(a, b):
    i = 0
    while i < len(a) and i < len(b) and a[i] == b[i]:
        i += 1
    return i

print('LCP array:')
lcp_array = [lcp(s[a: ], s[b: ]) for (a, b) in pairwise(sa)]
print(lcp_array)
