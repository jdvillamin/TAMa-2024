#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll power(ll b, ll e, ll m) {
	ll result = 1;
	while (e > 0) {
		if (e & 1)
			result = result * b % m;
		b = b * b % m;
		e >>= 1;
	}
	return result;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	ll N, m;
	cin >> N >> m;
	ll ans = 1;
	for (ll n = 2; n <= N; n++)
		ans = (ans + power(n, n - 2, m)) % m;
	cout << ans << "\n";	
	return 0;
}
