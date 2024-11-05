#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	ll n;
	cin >> n;
	vector<ll> b(n + 1);
	b[1] = 1;
	for (ll i = 2; i <= n; i++)
		b[i] = (21 * b[i - 1] + 17) % (1LL << 18);
	vector<ll> a(n + 1);
	for (ll i = 1; i <= n; i++)
		a[i] = b[i] % 6 + 1;
	vector<ll> faces(7);
	for (ll i = 1; i <= 6; i++)
		faces[i] = i;
	auto rotate = [&](ll face) {
		vector<ll> original_faces(7);
		for (ll i = 1; i <= 6; i++)
			original_faces[i] = faces[i];
		if (face == 1) {
			faces[2] = original_faces[4];
			faces[3] = original_faces[2];
			faces[5] = original_faces[3];
			faces[4] = original_faces[5];
		} else if (face == 2) {
			faces[3] = original_faces[6];
			faces[1] = original_faces[3];
			faces[4] = original_faces[1];
			faces[6] = original_faces[4];
		} else if (face == 3) {
			faces[1] = original_faces[5];
			faces[2] = original_faces[1];
			faces[6] = original_faces[2];
			faces[5] = original_faces[6];
		} else if (face == 4) {
			faces[2] = original_faces[6];
			faces[1] = original_faces[2];
			faces[5] = original_faces[1];
			faces[6] = original_faces[5];
		} else if (face == 5) {
			faces[1] = original_faces[4];
			faces[3] = original_faces[1];
			faces[6] = original_faces[3];
			faces[4] = original_faces[6];
		} else {
			faces[3] = original_faces[5];
			faces[2] = original_faces[3];
			faces[4] = original_faces[2];
			faces[5] = original_faces[4];
		}
	};
	vector<ll> f(7, 0);
	for (ll l = 1; l <= n; l++) {
		for (ll r = l; r <= n; r++) {
			for (ll i = 1; i <= 6; i++)
				faces[i] = i;
			for (ll i = l; i <= r; i++) {
				// find where a[i] is in
				for (ll face = 1; face <= 6; face++)
					if (faces[face] == a[i]) {
						rotate(face);
						break;
					}
			}
			f[faces[1]]++;
		}
	}
	ll ans = 0;
	for (ll i = 1; i <= 6; i++)
		ans = (ans + i * f[i]) % MOD;
	cout << ans << "\n";
	return 0;
}
