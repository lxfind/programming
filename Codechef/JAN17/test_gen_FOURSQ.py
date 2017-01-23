from random import randint
print 3
for i in range(0, 3):
    n = 100000
    q = 100000
    m = 1000000
    p = randint(100000000000, 1000000000000)
    print n, q, p
    for j in range(0, n):
        print randint(1, m),
    print
    for j in range(0, q):
        c = randint(1, 2)
        if c == 1:
            x = randint(1, n)
            y = randint(1, m)
            print c, x, y
        else:
            l = randint(1, n)
            r = randint(l, n)
            print c, l, r
