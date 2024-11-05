#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	ll r, c;
	cin >> r >> c;
	vector<vector<ll>> g(r, vector<ll>(c));
	for (ll i = 0; i < r; i++)
		for (ll j = 0; j < c; j++)
			g[i][j] = i + 1;
	vector<vector<ll>> dp(r, vector<ll>(c, 0));
	dp[0][0] = g[0][0];
	for (ll i = 0; i < r; i++)
		for (ll j = 0; j < c; j++) {
			if (i > 0)
				dp[i][j] = (dp[i][j] + g[i][j] * dp[i - 1][j]) % MOD;
			if (j > 0)
				dp[i][j] = (dp[i][j] + g[i][j] * dp[i][j - 1]) % MOD;
		}
	cout << dp[r - 1][c - 1] << "\n";
	return 0;
}
