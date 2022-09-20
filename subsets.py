from itertools import compress
def p(s, x): return list(compress(s, map(int, bin(x)[2:].zfill(len(s)))))

# No 'D's
mask = 0b111011

x = 0 

x = ((x | ~mask) + 1) & mask

while x:
    print(p('ABCDEF', x))
    x = ((x | ~mask) + 1) & mask
