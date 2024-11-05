#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353, MAX_N = 200000000;

ll inv(ll a) {
	return a <= 1 ? a : MOD - (MOD / a) * inv(MOD % a) % MOD;
}

ll f(ll a) {
	ll result = 1;
	for (ll i = 1; i <= a; i++)
		result = result * i % MOD;
	return result;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	// input n
	ll n;
	cin >> n;

	// generate n prime numbers
	vector<bool> is_prime(MAX_N + 1, true);
	vector<ll> prime;
	for (ll p = 2; p * p <= MAX_N; p++)
		if (is_prime[p])
			for (ll i = p * p; i <= MAX_N; i += p)
				is_prime[i] = false;
	for (ll p = 2; p <= MAX_N && (ll) prime.size() < n; p++)
		if (is_prime[p])
			prime.push_back(p);
	auto print_prime = [&]() -> void {
		for (ll i = 0; i < n; i++)
			cout << prime[i] << " \n"[i == n - 1];
	};
	// print_prime();

	// compute C(i, j)
	auto choose = [&](ll i, ll j) -> ll {
		ll den = (inv(f(j)) * inv(f(i - j))) % MOD;
		return f(i) * den % MOD;
	};

	ll c0 = choose(n - 0, n / 2 - 0);
	ll c1 = choose(n - 1, n / 2 - 1);
	ll c2 = choose(n - 2, n / 2 - 2);
	cout << "c0: " << c0 << "\n";
	cout << "c1: " << c1 << "\n";
	cout << "c2: " << c2 << "\n";

	// compute sum_{i = 1}^n p[i]
	ll sum_p = 0;
	for (ll i = 0; i < n; i++)
		sum_p = (sum_p + prime[i]) % MOD;
	cout << "sum_p: " << sum_p << "\n";

	// compute sig(sum(T)) = c1 * sum_{i = 1}^n p[i]
	ll sig_sum_T = c1 * sum_p % MOD;
	cout << "sig_sum_T: " << sig_sum_T << "\n";

	// compute 
	// sig((sum(T))^2) = S1 + 2 * S2
	// S1 = c1 * sum_{i = 1}^n p[i]^2 
	// S2 = c2 * sum_{1 <= i < j <= n} p[i][j]
	
	// compute sum_{i = 1}^n p[i]^2
	ll sum_p2 = 0;
	for (ll i = 0; i < n; i++)
		sum_p2 = (sum_p2 + prime[i] * prime[i]) % MOD;
	cout << "sum_p2: " << sum_p2 << "\n";

	// compute S1
	ll S1 = c1 * sum_p2 % MOD;
	cout << "S1: " << S1 << "\n";

	// compute sum_{1 <= i < j <= n} p[i]p[j]
	ll sum_pp = 0;
	ll prefix_sum = prime[0];
	for (ll i = 1; i < n; i++) {
		sum_pp = (sum_pp + prefix_sum * prime[i]) % MOD;
		prefix_sum = (prefix_sum + prime[i]) % MOD;
	}
	cout << "sum_pp: " << sum_pp << "\n";

	// compute S2
	ll S2 = c2 * sum_pp % MOD;
	cout << "S2: " << S2 << "\n";

	// compute S1 + S2
	ll sig_sum_T2 = (S1 + 2 * S2) % MOD;
	cout << "sig_sum_T2: " << sig_sum_T2 << "\n";

	// final sum S = 4 * sig_sum_T2 - 4 * sum_p * sig_sum_T + c0 * sum_p^2
	ll ans = 4 * sig_sum_T2 % MOD;
	ans = ((ans - (4 * sum_p % MOD) * sig_sum_T) % MOD + MOD) % MOD;
	ans = (ans + (c0 * sum_p % MOD) * sum_p) % MOD;
	cout << ans << "\n";	
	return 0;
}
