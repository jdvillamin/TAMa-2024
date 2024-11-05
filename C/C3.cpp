#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	ll ln, rn, lk, rk;
	cin >> ln >> rn >> lk >> rk;
	ll ans = (rn - ln + 1) * (rk - lk + 1) % MOD;
	for (ll k = lk; k <= rk; k++)
		ans = ((ans - (rn / k - (ln - 1) / k)) % MOD + MOD) % MOD;
	cout << ans << "\n";
	return 0;
}
