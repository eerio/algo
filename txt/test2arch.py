import os
import random
import string


def test(doc, inp):
    doc.write(inp)
    doc.flush()
    #os.system('cat input.in | ./wzorcowka.out > py.out')
    os.system('cat input.in | python3 zad2.py > py.out')
    os.system('cat input.in | ./a.out > cpp.out')
    doc.write('\0' * len(inp))
    doc.truncate(0)
    doc.seek(0)
    with open('py.out') as doc1:
        pyout = doc1.read()
    with open('cpp.out') as doc1:
        cppout = doc1.read()

    if pyout != cppout:
        print()
        print('Input:', inp)
        print('Python:', repr(pyout))
        print('Cpp:', repr(cppout))
        raise Exception('Invalid!')

with open('input.in', 'w+') as doc:
    """
    large = ''
    large += 'a' * 500000
    large += '\n'
    large += 'a' * 500000
    large += '\n'
    large += 'a' * 500000
    large += '\n'
    test(doc, large)
    with open('cpp.out') as doc1:
        cppout = doc1.read()

    values = list(map(int, cppout.split()))
    print(values[:20])
    assert values[0] == (500000 ** 3) % 1000000007
"""

    for inp in [
        'abc\nbc\ncbc',
        'abacaba\nabac\nabcd'
    ]:
        test(doc, inp)
    size = 10
    for size, ntests in [(25, 100000)]:
        for i in range(ntests):
            print(i, end='\r')
            inp = ''
            inp += ''.join(random.choices('ab', k=int(size * random.choice([0.5, 0.7, 0.9, 1.5, 2.5]))))
            inp += '\n'
            inp += ''.join(random.choices('ab', k=int(size * random.choice([0.5, 0.7, 0.9, 1.5, 2.5]))))
            inp += '\n'
            inp += ''.join(random.choices('ab', k=int(size * random.choice([0.5, 0.7, 0.9, 1.5, 2.5]))))
            inp += '\n'
            test(doc, inp)

print()
