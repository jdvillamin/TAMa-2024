#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	ll ln, rn, lk, rk;
	cin >> ln >> rn >> lk >> rk;
	ll M = 0, m = 0;
	for (ll n = ln; n <= rn; n++)
		for (ll k = lk; k <= rk; k++) {
			M = (M + (n + k - 1) / k) % MOD;
			m = (m + n / k) % MOD;
		}
	cout << ((M - m) % MOD + MOD) % MOD << "\n";
	return 0;
}
