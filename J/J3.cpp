#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<ll> Perm;
typedef vector<vector<ll>> Matrix;

const ll MOD = 998244353;

// zero-based indexing
Matrix permutation_to_matrix(const Perm &permutation) {
	ll n = permutation.size();
	Matrix matrix(n, vector<ll>(n, 0));
	for (ll i = 0; i < n; i++)
		matrix[permutation[i]][i] = 1;
	return matrix;
}

Matrix multiply_matrix(const Matrix &B, const Matrix &A) {
	assert(A[0].size() == B.size());
	ll n = A.size(), p = A[0].size(), m = B[0].size();
	Matrix C(n, vector<ll>(m, 0));
	for (ll i = 0; i < n; i++)
		for (ll j = 0; j < m; j++)
			for (ll k = 0; k < p; k++)
				C[i][j] += A[i][k] * B[k][j];
	return C;
}

Matrix get_transpose(const Matrix &A) {
	ll n = A.size(), m = A[0].size();
	Matrix transpose(m, vector<ll>(n));
	for (ll i = 0; i < n; i++)
		for (ll j = 0; j < m; j++)
			transpose[j][i] = A[i][j];
	return transpose;
}

bool equal(const Matrix &B, const Matrix &A) {
	assert(A.size() == B.size() && A[0].size() == B[0].size());
	ll n = A.size(), m = A[0].size();
	for (ll i = 0; i < n; i++)
		for (ll j = 0; j < m; j++)
			if (A[i][j] != B[i][j])
				return false;
	return true;
}

Matrix rotation(ll x) {
	Perm permutation;

	if (x == 0)
		permutation = {0, 2, 4, 1, 3, 5};
	else if (x == 1)
		permutation = {3, 1, 0, 5, 4, 2};
	else if (x == 2)
		permutation = {1, 5, 2, 3, 0, 4};
	else if (x == 3)
		permutation = {4, 0, 2, 3, 5, 1};
	else if (x == 4)
		permutation = {2, 1, 5, 0, 4, 3};
	else
		permutation = {0, 3, 1, 4, 2, 5};

	return permutation_to_matrix(permutation);
}

void print_permutation(Perm permutation) {
	ll n = permutation.size();
	for (ll i = 0; i < n; i++)
		cout << permutation[i] << " \n"[i == n - 1];
}

void print_matrix(Matrix matrix) {
	ll n = matrix.size(), m = matrix[0].size();
	for (ll i = 0; i < n; i++)
		for (ll j = 0; j < m; j++)
			cout << matrix[i][j] << " \n"[j == m - 1];
	cout << "\n";
}

int main() {
	ll n;
	cin >> n;
	
	// Compute sequence
	vector<ll> b(n), a(n);
	b[0] = 1;
	for (ll i = 1; i < n; i++)
		b[i] = (21 * b[i - 1] + 17) % (1 << 18);
	for (ll i = 0; i < n; i++)
		a[i] = b[i] % 6;

	vector<ll> f(6, 0); // f(x) = number of pairs (l, r) so that x is generated
	
	Perm p(6); // permutation of 0 to 5 which represents a state of a die
	for (ll i = 0; i < 6; i++)
		p[i] = i;
	
	ll counter = 0;	
	// Generate all permutations and count the number of (l, r) that generates that state
	// For each state, increase f(x) if p[x] = 1
	do {
		cout << (++counter) << "\n";
		Matrix target = permutation_to_matrix(p);
		// assert(equal(multiply_matrix(get_transpose(target), target), permutation_to_matrix({0, 1, 2, 3, 4, 5})));
		// print_matrix(target);
		Matrix dice = permutation_to_matrix({0, 1, 2, 3, 4, 5});
		map<Matrix, ll> prefix_products;
		prefix_products[dice]++;
		ll count = 0;
		
		for (ll i = 0; i < n; i++) {
			dice = multiply_matrix(rotation(a[i]), dice);
			
			/*
			 * M = A[j] * A[j - 1] * ... * A[i + 1]
			 * P[j] = A[j] * A[j - 1] * ... * A[0]
			 * P[i] = A[i] * A[i - 1] * ... * A[0]
			 * P[j] = M * P[i]
			 * M^(-1) * P[j] = P[i]
			 * Current dice = P[j]
			 * Seen dice = P[i]
			 */
			
			Matrix to_find = multiply_matrix(get_transpose(target), dice);
			
			if (prefix_products.find(to_find) != prefix_products.end())
				count = (count + prefix_products[to_find]) % MOD;

			prefix_products[dice]++;
		}

		// Identify what dot count is on top
		for (ll i = 0; i < 6; i++)
			if (p[i] == 0) {
				f[i] = (f[i] + count) % MOD;
				break;
			}
	} while (next_permutation(p.begin(), p.end()));

	// Compute the answer
	ll answer = 0;

	for (ll i = 0; i < 6; i++)
		answer = (answer + (i + 1) * f[i]) % MOD;
	
	cout << answer << "\n";

	return 0;
}
