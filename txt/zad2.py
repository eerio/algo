import itertools

s1 = input()
s2 = input()
s3 = input()

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
        print(cnt, end='')
    else:
        print(' ' + str(cnt), end='')
print()

