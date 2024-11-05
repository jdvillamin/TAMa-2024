#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> num, S;
ll dp[18][2][2][1 << 9][3][6][9];
// dp[pos][f][lead][mask][m3][m6][m9] - number of digitvisible numbers
// pos  - digit position
// f    - tightness
// mask - which digits are used
// m3   - modulo 3
// m6   - modulo 6
// m9   - modulo 9
// lead - if we can use 0

ll power_mod(ll b, ll e, ll m) {
	b %= m;
	ll r = 1;
	while (e > 0) {
		if (e & 1) {
			r = r * b % m;
		}
		b = b * b % m;
		e >>= 1;
	}
	return r;
}

ll call(ll pos, ll f, ll lead, ll mask, ll m3, ll m6, ll m9) {
	if (pos == (ll) num.size()) {
		ll good = 1;
		for (ll bit = 0; bit < 9; bit++) {
			if ((mask >> bit) & 1) {
				if (bit == 2 && m3 != 0) {
					return 0;
				}
				if (bit == 5 && m6 != 0) {
					return 0;
				}
				if (bit == 8 && m9 != 0) {
					return 0;
				}
			}
		}
		cout << "MASK: " << bitset<8>(mask) << "\n";
		cout << "MODULO: " << m9 << " " << m6 << " " << m3 << "\n";
		cout << "GOOD: " << good << "\n\n";
		return 1;
	}

	if (dp[pos][f][lead][mask][m3][m6][m9] != -1)
		return dp[pos][f][lead][mask][m3][m6][m9];

	ll res = 0;

	ll LMT = (f == 0 ? num[pos] : 9);
	
	for (ll d : S) {
		if (d == 0 && lead == 0)
			continue;
		if (d > LMT)
			break;
		ll nf = f;
		if (f == 0 && d < LMT)
			nf = 1;
		ll nmask = mask;
		ll nlead = d == 0;
		if (d == 1)
			nmask |= (1 << 0);
		if (d == 3)
			nmask |= (1 << 2);
		if (d == 6)
			nmask |= (1 << 5);
		if (d == 9)
			nmask |= (1 << 8);
		ll nm3 = ((m3 - power_mod(10, num.size() - 1 - pos, 3) * d) % 3 + 3) % 3;
		ll nm6 = ((m6 - power_mod(10, num.size() - 1 - pos, 6) * d) % 6 + 6) % 6;
		ll nm9 = ((m9 - power_mod(10, num.size() - 1 - pos, 9) * d) % 9 + 9) % 9;
		res += call(pos + 1, nf, nlead, nmask, nm3, nm6, nm9);
	}

	return dp[pos][f][lead][mask][m3][m6][m9] = res;
}

ll solve(ll b) {
	num.clear();
	while (b > 0) {
		num.push_back(b % 10);
		b /= 10;
	}
	reverse(num.begin(), num.end());
	for (ll i = 0; i < 18; i++)
		for (ll j = 0; j < 2; j++)
			for (ll k = 0; k < 2; k++)
				for (ll l = 0; l < (1 << 9); l++)
					for (ll m = 0; m < 3; m++)
						for (ll n = 0; n < 6; n++)
							for (ll b = 0; b < 9; b++)
								dp[i][j][k][l][m][n][b] = -1;
	ll res = call(0, 0, 1, 0, 0, 0, 0);
	return res;
}

int main() {
	ll n;
	cin >> n;
	S.push_back(0);
	for (ll i = 0; i < n; i++) {
		ll d;
		cin >> d;
		S.push_back(d);
	}
	ll l, r;
	cin >> l >> r;
	cout << solve(r) - solve(l - 1) << "\n";
	return 0;
}
