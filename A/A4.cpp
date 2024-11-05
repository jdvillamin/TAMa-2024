#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<vector<ll>> matrix;

const ll MOD = 998244353;

matrix multiply(const matrix &A, const matrix &B) {
	ll m = A.size(), n = B.size(), p = B[0].size();
	matrix result(m, vector<ll>(p));
	for (ll i = 0; i < m; i++)
		for (ll j = 0; j < p; j++)
			for (ll k = 0; k < n; k++)
				result[i][j] = (result[i][j] + A[i][k] * B[k][j]) % MOD;
	return result;
}

matrix add(const matrix &A, const matrix &B) {
	ll n = A.size(), m = A[0].size();
	matrix result(n, vector<ll>(m));
	for (ll i = 0; i < n; i++)
		for (ll j = 0; j < m; j++)
			result[i][j] = (A[i][j] + B[i][j]) % MOD;
	return result;
}

matrix matrix_exponentiation(matrix A, ll e) {
	ll n = A.size();
	matrix C(n, vector<ll>(n, 0));
	for (ll i = 0; i < n; i++)
		C[i][i] = 1;
	while (e > 0) {
		if (e & 1)
			C = multiply(A, C);
		A = multiply(A, A);
		e >>= 1;
	}
	return C;
}

matrix get_zero(ll n) {
	matrix A(n, vector<ll>(n, 0));
	return A;
}

matrix get_identity(ll n) {
	matrix A(n, vector<ll>(n, 0));
	for (ll i = 0; i < n; i++)
		A[i][i] = 1;
	return A;
}

// 1 + A + A^2 + ... + A^N
matrix sum_of_powers(matrix &A, ll N) {
	ll n = A.size();
	if (N == 0)
		return get_identity(n);
	matrix first_half = sum_of_powers(A, (N - 1) / 2);
	matrix multiplier = matrix_exponentiation(A, (N - 1) / 2 + 1);
	matrix second_half = multiply(multiplier, first_half);
	matrix result = add(first_half, second_half);
	if (N % 2 == 0) {
		matrix last_term = matrix_exponentiation(A, N);
		result = add(result, last_term);
	}
	return result;
}

void print_matrix(matrix A) {
	ll n = A.size(), m = A[0].size();
	for (ll i = 0; i < n; i++)
		for (ll j = 0; j < m; j++)
			cout << A[i][j] << " \n"[j == m - 1];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	ll N, k;
	cin >> N >> k;
	vector<vector<ll>> A(2 * k - 1, vector<ll>(2 * k - 1, 0));
	for (ll i = 1; i <= k; i++)
		A[0][i - 1] = i;
	for (ll i = k - 1; i >= 1; i--)
		A[0][k + (k - i) - 1] = i;
	ll row = 1, col = 0;
	while (row < 2 * k - 1) {
		A[row][col] = 1;
		row++;
		col++;
	}
	vector<vector<ll>> row_matrix(2 * k - 1, vector<ll>(1));
	for (ll i = 1; i <= 2 * k - 1; i++)
		row_matrix[i - 1][0] = 2 * k - i;
	matrix A_sum = sum_of_powers(A, N - (2 * k - 1));
	matrix final_row = multiply(A_sum, row_matrix);
	ll ans = final_row[0][0];
	for (ll i = 1; i < 2 * k - 1; i++)
		ans = (ans + i) % MOD;
	cout << ans << "\n";	
	return 0;
}
