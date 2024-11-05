#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353, MAX_N = 100000;
vector<ll> memo(MAX_N + 1, -1);

ll compute_m(ll n, ll k) {
	if (memo[n] != -1)
		return memo[n];
	if (1 <= n && n <= 2 * k - 1)
		return memo[n] = n % MOD;
	ll sum = 0;
	for (ll r = 1; r <= k; r++) {
		sum += r * compute_m(n - r, k);
		sum %= MOD;
	}
	for (ll r = k - 1; r >= 1; r--) {
		sum += r * compute_m(n - k - (k - r), k);
		sum %= MOD;
	}
	return memo[n] = sum;
}

int main() {
	ll N, k;
	cin >> N >> k;
	ll sum = 0;
	for (ll n = 1; n <= N; n++) {
		sum += compute_m(n, k);
		sum %= MOD;
	}
	cout << sum << "\n";
	return 0;
}
