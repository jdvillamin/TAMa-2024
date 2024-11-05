#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> Perm;
typedef vector<vector<ll>> Matrix;

const ll MOD = 998244353, BLOCK = 1 << 18, N = 1000000000000000000;

Perm inverse(const Perm &p) {
	ll n = p.size();

	Perm result(n);

	for (ll i = 0; i < n; i++)
		result[p[i]] = i;

	return result;
}

Perm permute(Perm p, Perm q) {
	ll n = p.size();
	
	Perm result(n);

	for (ll i = 0; i < n; i++)
		result[i] = p[q[i]];

	return result;
}

Perm rotation(ll x) {
	Perm result;

	if (x == 0)
		result = {0, 2, 4, 1, 3, 5};
	else if (x == 1)
		result = {3, 1, 0, 5, 4, 2};
	else if (x == 2)
		result = {1, 5, 2, 3, 0, 4};
	else if (x == 3)
		result = {4, 0, 2, 3, 5, 1};
	else if (x == 4)
		result = {2, 1, 5, 0, 4, 3};
	else
		result = {0, 3, 1, 4, 2, 5};
	
	return result;
}

ll small_counter(vector<ll> &a, vector<ll> &p, ll n) {
	Perm target = p;

	Perm dice = {0, 1, 2, 3, 4, 5};

	map<Perm, ll> prefix;

	prefix[dice]++;

	ll count = 0;

	for (ll i = 0; i < n; i++) {
		dice = permute(dice, rotation(a[i]));

		Perm to_find = permute(dice, inverse(target));

		if (prefix.find(to_find) != prefix.end())
			count = (count + prefix[to_find]) % MOD;

		prefix[dice]++;
	}

	return count;
}

ll arithmetic_mod3(ll head, ll tail, ll blocks) {
	ll a1  = blocks - head + 1;
	ll an  = blocks - tail + 1;
	ll n   = (a1 - an) / 3 + 1;
	ll sum = a1 + an;
	if (n % 2 == 0)
		n /= 2;
	else if (sum % 2 == 0)
		sum /= 2;
	ll result = (n % MOD) * (sum % MOD) % MOD;
	assert(result >= 0);
	return result;
}

ll less3(ll m, ll mod3) {
	for (ll i = m; i >= m - 6; i--)
		if (i % 3 == mod3)
			return i;
	return m;
}

void print_permutation(Perm permutation) {
	ll n = permutation.size();
	for (ll i = 0; i < n; i++)
		cout << permutation[i] << " \n"[i == n - 1];
}

int main() {
	Perm Q0 = {0, 1, 2, 3, 4, 5};
	Perm Q1 = {2, 0, 1, 4, 5, 3};
	Perm Q2 = permute(Q1, Q1);

	// Compute sequence
	vector<ll> b(BLOCK), a(BLOCK);
	b[0] = 1;
	for (ll i = 1; i < BLOCK; i++)
		b[i] = (21 * b[i - 1] + 17) % BLOCK;
	for (ll i = 0; i < BLOCK; i++)
		a[i] = b[i] % 6;

	vector<ll> f(6, 0); // f(x) = number of pairs (l, r) so that x is generated
	
	Perm dice(6); // permutation of 0 to 5 which represents a state of a die
	for (ll i = 0; i < 6; i++)
		dice[i] = i;
	
	// Generate all valid dices
	set<Perm> valid_dices;

	for (ll i = 0; i < 1000 /* Increase if size is not 24 */; i++) {
		valid_dices.insert(dice);
		dice = permute(dice, rotation(rand() % 6));
	}

	assert(valid_dices.size() == 24);

	// Compute prefix of permutations
	vector<Perm> prefix(BLOCK);
	prefix[0] = permute({0, 1, 2, 3, 4, 5}, rotation(a[0]));
	for (ll i = 1; i < BLOCK; i++)
		prefix[i] = permute(prefix[i - 1], rotation(a[i]));

	// Compute suffix of permutations
	vector<Perm> suffix(BLOCK);
	suffix[BLOCK - 1] = permute({0, 1, 2, 3, 4, 5}, rotation(a[BLOCK - 1]));
	for (ll i = BLOCK - 2; i >= 0; i--)
		suffix[i] = permute(rotation(a[i]), suffix[i + 1]);
	
	// Count instances of suffixes
	map<Perm, ll> suffix_count;
	for (ll i = BLOCK - 1; i >= 1; i--) {
		suffix_count[suffix[i]]++;
		suffix_count[suffix[i]] %= MOD;
	}

	ll counter = 0;	
	// Generate all permutations and count the number of (l, r) that generates that state
	// For each state, increase f(x) if p[x] = 1
	ll blocks = N / BLOCK;

	for (Perm p : valid_dices) {
		cout << ++counter << "\n";
		
		// Case when segments are inside a block
		ll block_count = small_counter(a, p, BLOCK);

		for (ll i = 0; i < 6; i++)
			if (p[i] == 0)
				f[i] = (f[i] + (blocks % MOD) * (block_count % MOD) % MOD) % MOD;

		// Case when we have only Q^k
		// k == 0 mod 3
		// Q^0 will not be included since this is empty
		// Q^3, Q^6, Q^9, ...
		// If Q^3, we have blocks - 2 ways
		// If Q^6, we have blocks - 5 ways
		// ...
		// So, we add (blocks - 2) + (blocks - 5) + ...
		
		// k == 1 mod 3
		// Q^1 will not be counted anymore since this is part of the block count
		// Q^4, Q^7, Q^10...
		// If Q^4, we have blocks - 3 ways
		// If Q^7, we have blocks - 6 ways
		// ...
		// So, we add (blocks - 3) + (blocks - 6) + ...

		// k == 2 mod 3
		// Q^2, Q^5, Q^8, ...
		// If Q^2, we have blocks - 1 ways
		// If Q^5, we have blocks - 4 ways
		// ...
		// So, we add (blocks - 1) + (blocks - 4) + ...

		ll case1 = 0;

		if (Q0 == p)
			case1 = (case1 + arithmetic_mod3(3, less3(blocks, 0), blocks)) % MOD;
		if (Q1 == p)
			case1 = (case1 + arithmetic_mod3(4, less3(blocks, 1), blocks)) % MOD;
		if (Q2 == p)	
			case1 = (case1 + arithmetic_mod3(2, less3(blocks, 2), blocks)) % MOD;

		// Case when we have L * Q^k
		// Q^0 case will also not be included 
		// k == 0 mod 3 -> Q^3, Q^6, Q^9, ... -> (blocks - 2) + (blocks - 5) + ...
		// k == 1 mod 3 -> Q^1, Q^4, Q^7, ... -> (blocks - 0) + (blocks - 3) + ...
		// k == 2 mod 3 -> Q^2, Q^5, Q^8, ... -> (blocks - 1) + (blocks - 4) + ...
		// L should always exist, so we can only have blocks = blocks - 1 to place Q^k
		// Run through all L
		ll case2 = 0;

		for (ll i = BLOCK - 1; i >= 1; i--) {
			if (permute(suffix[i], Q0) == p)
				case2 = (case2 + arithmetic_mod3(3, less3(blocks - 1, 0), blocks - 1)) % MOD;
			if (permute(suffix[i], Q1) == p)
				case2 = (case2 + arithmetic_mod3(1, less3(blocks - 1, 1), blocks - 1)) % MOD;
			if (permute(suffix[i], Q2) == p)
				case2 = (case2 + arithmetic_mod3(2, less3(blocks - 1, 2), blocks - 1)) % MOD;
		}

		// Case when we have Q^k * R
		// Q^0 case will also not be included
		// k == 0 mod 3 -> Q^3, Q^6, Q^9, ... -> (blocks - 2) + (blocks - 5) + ... + (blocks - N + 1).
		// k == 1 mod 3 -> Q^1, Q^4, Q^7, ... -> (blocks - 0) + (blocks - 3) + ... + (blocks - N + 1).
		// k == 2 mod 3 -> Q^2, Q^5, Q^8, ... -> (blocks - 1) + (blocks - 4) + ... + (blocks - N + 1).
		// R should always exist, so we can only have blocks = blocks - 1 to place Q^k
		// Run through all R
		ll case3 = 0;

		for (ll i = 0; i < BLOCK - 1; i++) {
			if (permute(Q0, prefix[i]) == p)
				case3 = (case3 + arithmetic_mod3(3, less3(blocks - 1, 0), blocks - 1)) % MOD;
			if (permute(Q1, prefix[i]) == p)
				case3 = (case3 + arithmetic_mod3(1, less3(blocks - 1, 1), blocks - 1)) % MOD;
			if (permute(Q2, prefix[i]) == p)
				case3 = (case3 + arithmetic_mod3(2, less3(blocks - 1, 2), blocks - 1)) % MOD;
		}

		// Case when we have L * Q^k * R
		// k == 0 mod 3 -> Q^0, Q^3, Q^6, ... -> (blocks - 1) + (blocks - 4) + ...
		// k == 1 mod 3 -> Q^1, Q^4, Q^7, ... -> (blocks - 2) + (blocks - 5) + ...
		// k == 2 mod 3 -> Q^2, Q^5, Q^8, ... -> (blocks - 3) + (blocks - 6) + ...
		// L and R should always exist, so we can only have blocks = blocks - 2 to place Q^k
		// L * Q^k * R == P
		// L           == P * (Q^k * R)^(-1)
		ll case4 = 0;

		for (ll i = 0; i < BLOCK - 1; i++) {
			Perm PQ0R = permute(p, inverse(permute(Q0, prefix[i])));
			Perm PQ1R = permute(p, inverse(permute(Q1, prefix[i])));
			Perm PQ2R = permute(p, inverse(permute(Q2, prefix[i])));
			if (suffix_count.find(PQ0R) != suffix_count.end())
				case4 = (case4 + arithmetic_mod3(0, less3(blocks - 2, 0), blocks - 2) * suffix_count[PQ0R] % MOD) % MOD;
			if (suffix_count.find(PQ1R) != suffix_count.end())
				case4 = (case4 + arithmetic_mod3(1, less3(blocks - 2, 1), blocks - 2) * suffix_count[PQ1R] % MOD) % MOD;
			if (suffix_count.find(PQ2R) != suffix_count.end())
				case4 = (case4 + arithmetic_mod3(2, less3(blocks - 2, 2), blocks - 2) * suffix_count[PQ2R] % MOD) % MOD;
		}

		for (ll i = 0; i < 6; i++)
			if (p[i] == 0) {
				f[i] = (f[i] + case1) % MOD;
				f[i] = (f[i] + case2) % MOD;
				f[i] = (f[i] + case3) % MOD;
				f[i] = (f[i] + case4) % MOD;
				assert(f[i] >= 0);
			}
	}

	// Compute the answer
	ll answer = 0;

	for (ll i = 0; i < 6; i++)
		answer = (answer + (i + 1) * f[i]) % MOD;
	
	cout << answer << "\n";

	return 0;
}
