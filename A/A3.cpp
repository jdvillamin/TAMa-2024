#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	ll N, k;
	cin >> N >> k;
	deque<ll> m_lower, m_upper;
	ll lower = 0, upper = 0;
	for (ll i = 1; i <= k; i++) {
		m_lower.push_front(i);
		lower = (lower + i) % MOD;
	}
	for (ll i = k + 1; i <= 2 * k - 1; i++) {
		m_upper.push_front(i);
		upper = (upper + i) % MOD;
	}
	ll total = (lower + upper) % MOD, m = 0;
	for (ll i = 1; i <= k; i++)
		m = (m + i * i) % MOD;
	for (ll i = k - 1; i >= 1; i--)
		m = (m + i * (k + (k - i))) % MOD;
	total = (total + m) % MOD;
	for (ll i = 2 * k + 1; i <= N; i++) {
		ll m0 = m;
		m = ((m - lower + upper + m) % MOD + MOD) % MOD;
		total = (total + m) % MOD;
		lower = ((lower - m_lower.back()) % MOD + MOD) % MOD;
		m_lower.pop_back();
		lower = (lower + m_upper.back()) % MOD;
		m_lower.push_front(m_upper.back());
		upper = ((upper - m_upper.back()) % MOD + MOD) % MOD;
		m_upper.pop_back();
		upper = (upper + m0) % MOD;
		m_upper.push_front(m0);
	}
	cout << total << "\n";
	return 0;
}
