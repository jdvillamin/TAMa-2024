#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;

vector<ll> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	vector<ll> p;
	for (ll i = 0; i < 3; i++)
		p.push_back(0);
	for (ll i = 0; i < 3; i++)
		p.push_back(1);
	ll ans = 0;
	do {
		ll t1 = 0, t2 = 0;
		for (ll i = 0; i < 6; i++)
			if (p[i])
				t1 += primes[i];
			else
				t2 += primes[i];
		ans = (ans + (t1 - t2) * (t1 - t2)) % MOD;
	} while (next_permutation(p.begin(), p.end()));
	cout << ans << "\n";
	return 0;
}
