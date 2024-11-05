#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 10000019, N = 60;

vector<vector<ll>> memo(N + 1, vector<ll>(N + 1, -1));

ll choose(ll n, ll m) {
	if (m > n) 
		return 0;
	if (memo[n][m] != -1)
		return memo[n][m];
	if (m == 0 || m == n)
		return memo[n][m] = 1;
	ll ans = (choose(n - 1, m) + choose(n - 1, m - 1)) % MOD;
	return memo[n][m] = ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	ll n, m;
	cin >> n >> m;
	ll ans = 0;
	for (ll i = m; i <= n; i++)
		ans = (ans + choose(n, i)) % MOD;
	cout << ans << "\n";
	return 0;
}
