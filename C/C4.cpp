#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;

ll count(ll n) {
	ll sqrtn = sqrtl(n), sum = 0;
	for (ll i = 1; i <= sqrtn; i++)
		sum = (sum + n / i) % MOD;
	sum = sum * 2 % MOD;
	sum = (sum - sqrtn * sqrtn) % MOD;
	return sum;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	ll ln = 5e14, rn = 1e15, rk = 5e14;
	// cin >> ln >> rn >> lk >> rk;
	ll ans = ((rn - ln + 1) % MOD) * (rk % MOD) % MOD;
	ll pairs = ((count(rn) - count(ln - 1)) % MOD + MOD) % MOD;
	pairs = ((pairs - (rn - ln) % MOD) % MOD + MOD) % MOD;
	ans = ((ans - pairs) % MOD + MOD) % MOD;
	cout << ans << "\n";
	return 0;
}
