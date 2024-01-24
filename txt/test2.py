import os
import random
import string


def test(doc, inp):
    doc.write(inp)
    doc.flush()
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
    for inp in [
        'abc\nbc\ncbc',
        'abacaba\nabac\nabcd'
    ]:
        test(doc, inp)
    size = 10
    for size, ntests in [(10, 100000)]:
        for i in range(ntests):
            print(i, end='\r')
            inp = ''.join(random.choices(string.ascii_uppercase, k=size))
            test(doc, inp)

print()
