#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 10000019;

ll f[MOD], inv[MOD];

ll legendre_formula(ll n, ll p = MOD) {
    ll power = 0;
    ll pk = p;
    while (pk <= n) {
        power += n / pk;
        if (pk > n / p) 
			break;
        pk *= p;
    }
    return power;
}

ll factmod(ll n) {
	ll res = 1LL;
	while (n > 1) {
		if ((n / MOD) % 2)
			res = MOD - res;
		res = res * f[n % MOD] % MOD;
		n /= MOD;
    }
    return res;
}

ll power(ll b, ll e) {
	ll res = 1LL;
	while (e > 0) {
		if (e & 1)
			res = res * b % MOD;
		b = b * b % MOD;
		e >>= 1;
	}
	return res;
}

int main() {
	ll n = 202400769120730662LL, m = 101200384561365331LL;
	f[0] = 1;
	for (ll i = 1; i < MOD; i++)
		f[i] = f[i - 1] * i % MOD;
	inv[0] = 1;
	inv[1] = 1;
	for (ll i = 2; i < MOD; i++)
    	inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
	ll ans = power(2, n - 1), fn = factmod(n), lfn = legendre_formula(n);
	auto compute = [&](ll i) -> ll {
		if (lfn - legendre_formula(i) - legendre_formula(n - i) > 0)
			return 0;
		return (fn * inv[factmod(i)] % MOD) * inv[factmod(n - i)] % MOD;;
	};
	ans = ((ans - compute(n / 2) * inv[2]) % MOD + MOD) % MOD;
	for (ll i = n / 2 + 1; i < m; i++) {
		ans = ((ans - compute(i)) % MOD + MOD) % MOD;
	}
	cout << ans << "\n";
	return 0;
}
