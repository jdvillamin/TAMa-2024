#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353, N = 600000000;

int main() {
	// ios::sync_with_stdio(false);
	// cin.tie(NULL);
	ll n;
	cin >> n;
	vector<ll> s(N + 1);
	s[1] = 1;
	s[2] = 2;
	ll last = 2, current = 2;
	for (ll i = 2; i <= N; i++) {
		for (ll k = 0; k < s[i] && last <= N; k++)
			s[last++] = current;
		current++;
	}
	ll nearest_sum = 0, i = 1, sum_i = 0;
	for (; i <= N && nearest_sum + i * s[i] <= n; i++) {
		nearest_sum += i * s[i];
		sum_i += s[i];
	}
	cout << "Difference: " << n - nearest_sum << "\n";
	cout << "Nearest sum: " << nearest_sum << "\n";
	cout << "i: " << i << "\n";
	cout << "Sum of i: " << sum_i << "\n";
	ll j = sum_i + 1;
	for (; j <= N && nearest_sum + s[j] <= n; j++)
		nearest_sum += s[j];
	cout << "Difference: " << n - nearest_sum << "\n";
	cout << "Nearest sum: " << nearest_sum << "\n";
	cout << "j: " << j << "\n";
	ll final_sum = 0;
	for (ll k = 1; k < j; k++)
		final_sum = (final_sum + k * s[k]) % MOD;
	final_sum = (final_sum + j * (n - nearest_sum)) % MOD;
	cout << "Final sum: " << final_sum << "\n";
	cout << "Answer: " << (final_sum * final_sum) % MOD << "\n";
	return 0;
}
