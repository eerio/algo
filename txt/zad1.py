import re 

s = input()
result = []

if s[0] == s[-1]:
    result += [(1, s.count(s[0]))]

for i in range(2, len(s) + 1):
    if not s[: i] == s[-i: ]:
        continue
    occ = len(re.findall(s[0] + f'(?={s[1: i]})', s))
    result += [(i, occ)]
print(len(result))
for pref, length in result:
    print(pref, length)
