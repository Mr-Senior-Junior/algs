import numpy as np

N = 10000

a = [1 for _ in range(N)]
for i in range(2, N):
    if a[i]:
        ind = i * i
        while ind < N:
            a[ind] = 0
            ind += i

counter = 0
for i in range(2, N):
    if (a[i]):
        counter += 1
        print("{:5}".format(i), end=' ')
        if counter == 20:
            counter = 0
            print()
