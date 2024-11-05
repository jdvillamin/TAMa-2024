#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;

ll power(ll b, ll e) {
	b %= MOD;
	ll result = 1;
	while (e > 0) {
		if (e & 1)
			result = result * b % MOD;
		b = b * b % MOD;
		e >>= 1;
	}
	return result;
}

ll inv(ll a) {
	return a <= 1 ? a : MOD - (MOD / a) * inv(MOD % a) % MOD;
}

ll rS(ll n, ll k) {
	ll result = 0;
	ll sign = k % 2 == 0 ? 1 : -1;
	vector<ll> f(k + 1);
	f[0] = 1;
	for (ll i = 1; i <= k; i++)
		f[i] = i * f[i - 1] % MOD;
	for (ll i = 0; i <= k; i++) {
		ll in = power(i, n);
		ll denominator = inv(f[k - i]) * inv(f[i]) % MOD;
		result = ((result + sign * in * denominator) % MOD + MOD) % MOD;
		sign *= -1;
	}
	return f[k] * result % MOD;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	ll r, c;
	cin >> r >> c;
	cout << rS(r + c - 1, r) << "\n";
	return 0;
}
