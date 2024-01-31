import random
from string import ascii_lowercase as A
import itertools

def gen(s1, s2, s3, alph1, alph2, alph3):
    inp = ''
    inp += ''.join(random.choices(alph1, k=s1))
    inp += '\n'
    inp += ''.join(random.choices(alph2, k=s2))
    inp += '\n'
    inp += ''.join(random.choices(alph3, k=s3))
    inp += '\n'
    return inp

B = 'ab'

def brut(inp):
    s1, s2, s3 = inp.split()
    ret = ''
    for l in range(1, min(len(s1), len(s2), len(s3)) + 1):
        cnt = 0
        for (i1, i2, i3) in itertools.product(
            range(len(s1) - l + 1),
            range(len(s2) - l + 1),
            range(len(s3) - l + 1)
        ):
            if s1[i1: i1 + l] == s2[i2: i2 + l] == s3[i3: i3 + l]:
                cnt += 1
        if l == 1:
            ret += str(cnt)
        else:
            ret += ' ' + str(cnt)
    return ret + '\n'


for i in range(1, 100):
    inp = gen(1, 1, 1, A, A, A)
    with open(f'tests/small/test_1_{i}.in', 'w+') as doc:
        doc.write(inp)
    with open(f'tests/small/test_1_{i}.out', 'w+') as doc:
        doc.write(brut(inp))

for i in range(1, 10000):
    inp = gen(5, 5, 5, A, A, A)
    with open(f'tests/small/test_2_{i}.in', 'w+') as doc:
        doc.write(inp)
    with open(f'tests/small/test_2_{i}.out', 'w+') as doc:
        doc.write(brut(inp))

for i in range(1, 10000):
    inp = gen(10, 9, 8, B, B, B)
    with open(f'tests/small/test_3_{i}.in', 'w+') as doc:
        doc.write(inp)
    with open(f'tests/small/test_3_{i}.out', 'w+') as doc:
        doc.write(brut(inp))

for i in range(1, 10000):
    inp = gen(10, 11, 12, A, A, A)
    with open(f'tests/small/test_4_{i}.in', 'w+') as doc:
        doc.write(inp)
    with open(f'tests/small/test_4_{i}.out', 'w+') as doc:
        doc.write(brut(inp))

for i in range(1, 10000):
    inp = gen(20, 21, 19, B, B, B)
    with open(f'tests/small/test_5_{i}.in', 'w+') as doc:
        doc.write(inp)
    with open(f'tests/small/test_5_{i}.out', 'w+') as doc:
        doc.write(brut(inp))

for i in range(1, 10000):
    inp = gen(37, 41, 33, B, B, A)
    with open(f'tests/small/test_6_{i}.in', 'w+') as doc:
        doc.write(inp)
    with open(f'tests/small/test_6_{i}.out', 'w+') as doc:
        doc.write(brut(inp))

for i in range(1, 10000):
    inp = gen(51, 40, 29, B, A, B)
    with open(f'tests/small/test_7_{i}.in', 'w+') as doc:
        doc.write(inp)
    with open(f'tests/small/test_7_{i}.out', 'w+') as doc:
        doc.write(brut(inp))
