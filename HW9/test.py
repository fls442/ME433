import numpy as np

v = [0, 1, 2, 3, 4, 5, 6, 7, 8 , 9]
f = []
h = [0.6, 0.1, 0.1, 0.2]


pts = len(h)


for ii in range(pts-1, len(v), 1):
    start = ii-pts+1
    # print("first index: " + str(start) + "\tval: " + str(v[start]) + "\tlast index: " + str(ii) + "\tval: " + str(v[ii]) + "\tsum: " + str(summ))
    # f.append(sum(v[start:ii+1])/pts)
    vals = v[start:ii+1]
    mult = zip(h, vals)
    avg = sum([a * b for a, b in mult])
    f.append(avg)

# C = zip(A, B) 
# D = [a * b for a, b in C]

for el in f:
    print(str(el))










