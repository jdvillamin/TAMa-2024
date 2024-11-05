#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<ll> num, S;
ll dp[18][2][2][256][5][7][8][9];
// dp[pos][f][lead][mask][m3][m6][m9] - number of digitvisible numbers
// pos  - digit position
// f    - tightness
// mask - which digits are used
// m5   - modulo 5
// m7   - modulo 7
// m8   - modulo 8
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

ll call(ll pos, ll f, ll lead, ll mask, ll m5, ll m7, ll m8, ll m9) {
	if (pos == (ll) num.size()) {
		for (ll bit = 0; bit < 8; bit++) {
			if ((mask >> bit) & 1) {
				if (bit == 0 && (m8 % 2 != 0))
					return 0;
				if (bit == 1 && (m9 % 3 != 0))
					return 0;
				if (bit == 2 && (m8 % 4 != 0))
					return 0;
				if (bit == 3 && (m5 != 0))
					return 0;
				if (bit == 4 && (m8 % 2 != 0 || m9 % 3 != 0))
					return 0;
				if (bit == 5 && (m7 != 0))
					return 0;
				if (bit == 6 && (m8 != 0))
					return 0;
				if (bit == 7 && (m9 != 0))
					return 0;
			}
		}
		// cout << "MASK: " << bitset<8>(mask) << "\n";
		// cout << "MODULO: " << m9 << " " << m8 << " " << m7 << " " << m5 << "\n";
		return 1;
	}

	if (dp[pos][f][lead][mask][m5][m7][m8][m9] != -1)
		return dp[pos][f][lead][mask][m5][m7][m8][m9];

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
		if (d > 1)
			nmask |= (1 << (d - 2));
		ll nm5 = ((m5 - power_mod(10, num.size() - 1 - pos, 5) * d) % 5 + 5) % 5;
		ll nm7 = ((m7 - power_mod(10, num.size() - 1 - pos, 7) * d) % 7 + 7) % 7;
		ll nm8 = ((m8 - power_mod(10, num.size() - 1 - pos, 8) * d) % 8 + 8) % 8;
		ll nm9 = ((m9 - power_mod(10, num.size() - 1 - pos, 9) * d) % 9 + 9) % 9;
		res += call(pos + 1, nf, nlead, nmask, nm5, nm7, nm8, nm9);
	}

	return dp[pos][f][lead][mask][m5][m7][m8][m9] = res;
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
				for (ll l = 0; l < (1 << 8); l++)
					for (ll m = 0; m < 5; m++)
						for (ll n = 0; n < 7; n++)
							for (ll b = 0; b < 8; b++)
								for (ll v = 0; v < 9; v++)
									dp[i][j][k][l][m][n][b][v] = -1;
	ll res = call(0, 0, 1, 0, 0, 0, 0, 0);
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
