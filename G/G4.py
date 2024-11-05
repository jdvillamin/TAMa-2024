import sys
sys.set_int_max_str_digits(2000000)

MOD = 998244353
s = '$' + str(12 ** 123456)
print(s)

"""
n = len(s)
s = '$' + s # Make it 1-indexed
print(s)
print(len(s))

For each i:
    1. For each l paired with i, there are 2^(l - 2 + n - i) partitions that will make the original copy of d[i] to be at position i + l - 1. If l = 1, then there are 2^(n - i) ways.
    2. For each r paired with i, there are 2^(n - r - 2 + i) partitions that will make the dupliccate copy of d[i] to be at position i + r. If r = n, then there are 2^(i - 1) ways.

Let's get the sum of digits that can get transfered to index i. Multiply it with the power of 10 for that digits place. Take it modulo M.

What is the initial complexity without optimizations? It's O(|s|^2) because we consider each l and r for each i.

There's maybe an optimization for this.

Original: From i to i + l - 1. 
Case: l > 1.
Number of partitions: 2^((l - 2) + (n - i)).

For each l from 1 to i, we add d[i] * 2^((l - 2) + (n - i)) to place[i + l - 1].
Thus, we add d[i] * 2^((l - 2) + (n - i)) * 10^(2 * n - (i + l - 1)) to the answer.

As l increases, note that (l - 2) + (n - i) increases while 2 * n - (i + l - 1) decreases.

Note that the sum has the following form:
    2^l1 * 10^l2 + 2^(l1 + 1) * 10^(l2 - 1) + ... + 2^(r1 - 1) * 10^(r2 - 1) + 2^r1 * 10^r2.
This sum is just:
    2^l1 * 10^r2 * (10^(l2 - r2) + 2 * 10^(l2 - r2 - 1) + ... + 2^(r1 - l1 - 1) * 10 + 2^(r1 - l1)).
l1 = n - i (l == 2)
l2 = 2 * n - (i + 1) (l == 2)
r1 = n - 2 (l == i)
r2 = 2 * n - (2 * i - 1) (l == i)

Case: l = 1.
Number of partitions: 2^(n - i).

Just add d[i] * 2^(n - i) * 10^(2 * n - i) to the answer.

Duplicate: From i to i + r.
Case: r < n. 
Number of partitions: 2^((i - 1) + (n - r - 1)).

For each r from i to n, we add d[i] * 2^((i - 1) + (n - r - 1)) to place[i + r].
Thus, we add d[i] * 2^((i - 1) + (n - r - 1)) * 10^(2 * n - (i + r)).

As r increases, note that (i - 1) + (n - r - 1) and 2 * n - (i + r) decreases.

Note that 2^((i - 1) + (n - r - 1)) * 10^(2 * n - (i + r)) has the following form:
    2^l1 * 10^l2 + 2^(l1 - 1) * 10^(l2 - 1) + 2^(l1 - 2) * 10^(l2 - 2) + ... + 2^r1 * 10^r2
This sum is just:
    2^r1 * 10^r2 * (2^(l1 - r1) * 10^(l2 - r2) + 2^(l1 - r1 - 1) * 10^(l2 - r2 - 1) + ... + 1).
l1 = n - 2 (r == i)
l2 = 2 * n - 2 * i (r == i)
r1 = i - 1 (r == n - 1)
r2 = n - i + 1 (r == n - 1)

Case: r = n
Number of partitions: 2^(i - 1).

Just add d[i] * 2^(i - 1) * 10^(n - i).
"""
