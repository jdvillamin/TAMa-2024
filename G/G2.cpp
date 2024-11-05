#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	ll s;
	string n;
	cin >> s >> n;
	ll ans = 0;
	for (ll mask = 1LL << (s - 1); mask < (1LL << s); mask++) {
		string result = "", duplicate = "";
		for (ll bit = 0; bit < s; bit++) {
			duplicate += n[bit];
			// cout << duplicate << " ";
			if ((mask >> bit) & 1) {
				result.append(duplicate);
				result.append(duplicate);
				duplicate.clear();
			}
		}
		// cout << "\n";
		// cout << result << "\n";
		ll power10 = 1;
		for (ll i = 2 * s - 1; i >= 0; i--) {
			ans = (ans + power10 * (result[i] - '0')) % MOD;
			power10 = power10 * 10 % MOD;	
		}
	}
	cout << ans << "\n";
	return 0;
}
