#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	ll n;
	cin >> n;
	vector<ll> s(n + 1);
	s[1] = 1;
	s[2] = 2;
	ll last = 2, current = 2;
	for (ll i = 2; i <= n; i++) {
		for (ll k = 0; k < s[i] && last <= n; k++)
			s[last++] = current;
		current++;
	}
	ll row_sum = 0;
	for (ll i = 1; i <= n; i++)
		row_sum = (row_sum + s[i]) % MOD;
	ll ans = 0;
	for (ll i = 1; i <= n; i++)
		ans = (ans + s[i] * row_sum) % MOD;
	cout << ans << "\n";
	return 0;
}
