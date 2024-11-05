#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Congruence {
	ll a, m;
};

ll power(ll p, ll k) {
	if (p == 0)
		return 0;
	ll result = 1;
	while (k > 0) {
		if (k & 1)
			result *= p;
		p *= p;
		k >>= 1;
	}
	return result;
}

ll power_mod(ll b, ll e, ll m) {
	if (b == 0)
		return 0;
	ll result = 1;
	while (e > 0) {
		if (e & 1)
			result = result * b % m;
		b = b * b % m;
		e >>= 1;
	}
	return result;
}

ll extended_gcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	ll x1, y1;
	ll gcd = extended_gcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
	return gcd;
}

ll mod_inv(ll a, ll m) {
	ll x, y;
	ll g = extended_gcd(a, m, x, y);
	if (g != 1) {
		throw runtime_error("Modular inverse does not exist");
	}
	return (x % m + m) % m; // Ensure the result is positive
}

__int128_t chinese_remainder_theorem(vector<Congruence> const &congruences) {
	__int128_t M = 1;
	for (auto const &congruence : congruences)
		M *= congruence.m;
	__int128_t solution = 0;
	for (auto const &congruence : congruences) {
		__int128_t a_i = congruence.a;
		__int128_t M_i = M / congruence.m;
		__int128_t N_i = mod_inv(M_i, congruence.m);
		solution = (solution + (a_i * M_i % M) * N_i) % M;
	}
	return (ll) solution;
}

vector<pair<ll, ll>> prime_factorize(ll m) {
	vector<pair<ll, ll>> factorization;
	for (ll d = 2; d * d <= m; d++) {
		if (m % d == 0) {
			pair<ll, ll> prime_power;
			prime_power.first = d;
			prime_power.second = 0;
			while (m % d == 0) {
				prime_power.second++;
				m /= d;
			}
			factorization.push_back(prime_power);
		}
	}
	if (m > 1)
		factorization.push_back({m, 1});
	return factorization;
}

ll multiply(ll a, ll b, ll m) {
	return (a % m) * (b % m) % m;
}

ll add(ll a, ll b, ll m) {
	return ((a % m) + (b % m)) % m;
}

// b^1 + b^2 + ... + b^N
ll sum_of_powers(ll b, ll N, ll m) {
	if (N == 0)
		return 0;
	if (N == 1)
		return b;
	ll lower_half = sum_of_powers(b, N / 2, m);
	ll multiplier = power_mod(b, N / 2, m);
	ll upper_half = multiply(multiplier, lower_half, m);
	ll sum_powers = add(lower_half, upper_half, m);
	if (N & 1) {
		ll term = power_mod(b, N, m);
		sum_powers = add(sum_powers, term, m);
	}
	return sum_powers;
}

int main() {
	// ios::sync_with_stdio(false);
	// cin.tie(NULL);
	ll N, M;
	cin >> N >> M;
	// compute sum(n^(n - 2)) mod p^k for each p^k that divides m
	// compute sum(n^(n - 2)) from n = 1 to n = p^(k + 1) - p^k
	// cycle is p^(k + 1) - p^k = lcm(p^k, (p - 1)p^(k - 1))
	vector<pair<ll, ll>> factorization = prime_factorize(M);
	// cout << "Factorization:\n";
	// for (auto prime_power : factorization)
		// cout << prime_power.first << " " << prime_power.second << "\n";
	// store congruences
	vector<Congruence> congruences;
	for (auto prime_power : factorization) {
		// cout << "\n\n";
		ll p = prime_power.first;
		ll k = prime_power.second;

		if (p == 1000003) {
			ll cycle_sum = 0;
			for (ll n = 1; n <= p; n++)
				cycle_sum = add(cycle_sum, sum_of_powers(n, p - 1, p), p);
			cout << "Cycle sum: " << cycle_sum << "\n";

			ll remainder = 0;
			for (ll n = N - N % (p * p - p) + 1; n <= N; n++)
				remainder = add(remainder, power_mod(n % p, n - 2, p), p);
			cout << "Remainder: " << remainder << "\n";
			
			ll sum = add(multiply(N / (p * p - p), cycle_sum, p), remainder, p);
			cout << "Sum: " << sum << "\n";

			Congruence congruence;
			congruence.a = sum;
			congruence.m = p;
			congruences.push_back(congruence);
			continue;
		}

		ll pk = power(p, k);
		ll cycle = pk * p - pk;
		cout << "p: " << p << "\n";
		cout << "k: " << k << "\n";
		cout << "Cycle: " << cycle << "\n";
		
		// compute the first cycle terms
		ll multiplier = k;
		ll initial_sum = 0;
		for (ll n = 1; n <= multiplier * cycle && n <= N; n++) {
			ll base = n % pk;
			if (base == 0)
				continue;
			ll term = power_mod(base, n - 2, pk);
			initial_sum = add(initial_sum, term, pk);
		}
		cout << "Initial sum: " << initial_sum << "\n";
		
		// compute quotient sum
		ll quotient_sum = 0;
		// assert((multiplier + 1) * cycle <= N);
		for (ll n = multiplier * cycle + 1; n <= (multiplier + 1) * cycle; n++) {
			assert(n - 2 >= k);
			ll base = n % pk;
			if (base == 0)
				continue;
			if (n % p == 0)
				continue;
			ll term = power_mod(base, n - 2, pk);
			quotient_sum = add(quotient_sum, term, pk);
		}
		cout << "Quotient sum: " << quotient_sum << "\n";
		
		// compare with next quotient sum	
		ll quotient_sum2 = 0;
		// assert((multiplier + 2) * cycle <= N);
		for (ll n = (multiplier + 1) * cycle + 1; n <= (multiplier + 2) * cycle; n++) {
			assert(n - 2 >= k);
			ll base = n % pk;
			if (base == 0)
				continue;
			if (n % p == 0)
				continue;
			ll term = power_mod(base, n - 2, pk);
			quotient_sum2 = add(quotient_sum2, term, pk);
		}
		assert(quotient_sum == quotient_sum2);
		cout << "Quotient sum 2: " << quotient_sum2 << "\n";
		
		// compute the excess terms
		ll remainder_sum = 0;
		// assert((multiplier + 1) * cycle < N - N % cycle + 1);
		for (ll n = max((multiplier + 1) * cycle + 1, N / cycle * cycle + 1); n <= N; n++) {
			assert(n - 2 >= k);
			ll base = n % pk;
			if (base == 0)
				continue;
			if (n % p == 0)
				continue;
			ll term = power_mod(base, n - 2, pk);
			remainder_sum = add(remainder_sum, term, pk);
		}
		
		cout << "Remainder sum: " << remainder_sum << "\n";
		ll cycle_quotient_sum = multiply((N / cycle - multiplier > 0 ? N / cycle - multiplier : 0), quotient_sum, pk);
		ll sum = 0;
		sum = add(initial_sum, cycle_quotient_sum, pk);
		sum = add(sum, remainder_sum, pk);
		cout << "Sum: " << sum << "\n";
		
		Congruence congruence;
		congruence.a = sum;
		congruence.m = pk;
		congruences.push_back(congruence);
	}
	cout << "Congruences:\n";
	for (auto congruence : congruences)
		cout << congruence.a << " " << congruence.m << "\n";

	// solve using chinese remainder theorem
	__int128_t answer = chinese_remainder_theorem(congruences);
	cout << "Answer: " << (ll) answer % M << "\n";
	return 0;
}
