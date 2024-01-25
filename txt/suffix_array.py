from itertools import pairwise
s1 = input()
s2 = input()
s3 = input()

s = s1 + '1' + s2 + '2' + s3 + '3'


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
lcpa = [lcp(s[a: ], s[b: ]) for (a, b) in pairwise(sa)]
print(lcpa)

for i in range(len(sa) - 2):
    i1, i2, i3 = sa[i], sa[i + 1], sa[i + 2]
    # sentinel of s1 has to be smaller than sentinels of s2, s3!
    
    print('lcp:', lcpa[i], lcpa[i + 1])
    print(s[i1: ], s[i2: ], s[i3: ])
