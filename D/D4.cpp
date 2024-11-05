#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353, N = 20000000;

ll arithmetic(ll l, ll r) {
	if (l > r)
		return 0;
	ll n = r - l + 1;
	return (n * (r + l) / 2) % MOD;
}

int main() {
	// ios::sync_with_stdio(false);
	// cin.tie(NULL);
	ll n;
	cin >> n;
	vector<ll> s(N + 1), is(N + 1), sum_s(N + 1), sum_is(N + 1);
	s[1] = 1;
	s[2] = 2;
	ll last = 2, current = 2;
	for (ll i = 2; i <= N; i++) {
		for (ll k = 0; k < s[i] && last <= N; k++)
			s[last++] = current;
		current++;
	}
	for (ll i = 1; i <= N; i++)
		is[i] = i * s[i];
	for (ll i = 1; i <= N; i++)
		sum_s[i] = sum_s[i - 1] + s[i];
	for (ll i = 1; i <= N; i++)
		sum_is[i] = sum_is[i - 1] + is[i];
	cout << "max reach sum_s: " << sum_s[N] << "\n";
	cout << "max reach sum_is: " << sum_is[N] << "\n";

	// find highest sum_is[i] that is less than n
	ll max_index = 1;
	for (ll i = 1; i <= N; i++)
		if (sum_is[i] < n)
			max_index = i;
	cout << "max_index: " << max_index << "\n";	

	// find difference
	ll difference = n - sum_is[max_index];
	cout << "difference: " << difference << "\n";
	
	ll ans = 0;
	// handle if difference is 0
	// if difference is 0, then directly get sum up to max_index
	for (ll i = 1; i <= max_index; i++)
		ans = (ans + i * arithmetic(sum_s[i - 1] + 1, sum_s[i])) % MOD;
	cout << "initial ans: " << ans << "\n";

	// we first add the "excess" terms
	// what is s[s[max_index]]? that is sum_s[max_index]
	// so next will be sum_s[max_index] + 1
	// what is the frequency of s[n]? it is max_index + 1
	// s[n] = sum_s[max_index] + (difference + max_index) / (max_index + 1)
	ll left = sum_s[max_index] + 1;
	ll right = sum_s[max_index] + difference / (max_index + 1);
	ll quotient = (max_index + 1) * arithmetic(left, right) % MOD;
	ll remainder = (difference % (max_index + 1)) * (sum_s[max_index] + (difference + max_index) / (max_index + 1)) % MOD;
	ans = (ans + quotient + remainder) % MOD;
	cout << ans << "\n";
	cout << "ans^2: " << (ans * ans) % MOD << "\n";

	return 0;
}
