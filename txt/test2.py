import os
import random
import string
from pathlib import Path
import tqdm

p = Path('tests/small')

for file in tqdm.tqdm(p.glob('**/*BIG*.out')):
    inp = file.with_suffix('.in')
    out = file.with_suffix('.cppout')
    os.system(f'cat {inp} | ./a.out > {out}')

    with open(file) as doc1:
        pyout = doc1.read()
    with open(out) as doc1:
        cppout = doc1.read()

    if pyout != cppout:
        print()
        with open(inp) as doc:
            inpp = doc.read()
        #print('Input:', inpp)
        #print('Python:', repr(pyout))
        print('Cpp:', repr(cppout)[:300])
        raise Exception('Invalid!')
