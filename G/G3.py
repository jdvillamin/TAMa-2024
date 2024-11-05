MOD = 998244353
s = str(11 ** 123)
n = len(s)
s = '$' + s # Make it 1-indexed
print(s)

"""
For each i:
    1. For each l paired with i, there are 2^(l - 2 + n - i) partitions that will make the original copy of d[i] to be at position i + l - 1. If l = 1, then there are 2^(n - i) ways.
    2. For each r paired with i, there are 2^(n - r - 2 + i) partitions that will make the dupliccate copy of d[i] to be at position i + r. If r = n, then there are 2^(i - 1) ways.

Let's get the sum of digits that can get transfered to index i. Multiply it with the power of 10 for that digits place. Take it modulo M.

What is the initial complexity without optimizations? It's O(|s|^2) because we consider each l and r for each i.

There's maybe an optimization for this.
"""

def power_mod(b, e, m):
    r = 1
    while e > 0:
        if e & 1:
            r = r * b % m
        b = b * b % m
        e >>= 1
    return r

def multiply(a, b, m):
    return (a % m) * (b % m) % m

def add(a, b, m):
    return (a % m + b % m) % m

def subtract(a, b, m):
    return ((a - b) % m + m) % m

place = [0 for _ in range(2 * n + 1)] # Sum of digits at the i-th place is place[i]

for i in range(1, n + 1):
    for l in range(1, i + 1):
        partitions = power_mod(2, n - i, MOD)
        if l > 1:
            partitions = power_mod(2, l - 2 + n - i, MOD)
        original_index = i + l - 1
        term = multiply(partitions, int(s[i]), MOD)
        place[original_index] = add(place[original_index], term, MOD)
    for r in range(i, n + 1):
        partitions = power_mod(2, i - 1, MOD)
        if r < n:
            partitions = power_mod(2, n - r - 1 + i - 1, MOD)
        duplicate_index = i + r
        term = multiply(partitions, int(s[i]), MOD)
        place[duplicate_index] = add(place[duplicate_index], term, MOD)

# Compute the final sum
answer = 0

for i in range(1, 2 * n + 1):
    answer = add(answer, multiply(power_mod(10, 2 * n - i, MOD), place[i], MOD), MOD)

print(answer)
