#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll power_mod(ll b, ll e, ll m) {
    ll r = 1;
    b %= m;
    while (e > 0) {
        if (e & 1) {
            r = (r * b) % m;
        }
        b = (b * b) % m;
        e >>= 1;
    }
    return r;
}

ll multiply(ll a, ll b, ll m) {
    return ((a % m) * (b % m)) % m;
}

ll add(ll a, ll b, ll m) {
    return ((a % m) + (b % m)) % m;
}

// x^n + x^(n - 1) + ... + 1
ll sum_power(ll x, ll n, ll m) {
    if (n == 0) return 1;
    ll first_half = sum_power(x, (n - 1) / 2, m);
    ll multiplier = power_mod(x, (n + 1) / 2, m);
    ll after_half = multiply(multiplier, first_half, m);
    ll result_sum = add(first_half, after_half, m);
    if (n % 2 == 0) {
        result_sum = add(result_sum, power_mod(x, n, m), m);
    }
    return result_sum;
}

// x^n + x^(n - 1) * y + ... + x * y^(n - 1) + y^n
ll sum_power2(ll x, ll y, ll n, ll m) {
    if (n == 0) return 1;
    ll x2 = multiply(x, x, m);
    ll y2 = multiply(y, y, m);
    ll sum1 = sum_power2(x2, y2, n / 2, m);
    if (n % 2 == 1) {
        return multiply(add(x, y, m), sum1, m);
    } else {
        return add(sum1, multiply(multiply(x, y, m), sum_power2(x2, y2, n / 2 - 1, m), m), m);
    }
}

ll sum_power1_general(ll x, ll y, ll l1, ll l2, ll r1, ll r2, ll m) {
    assert(l1 - r1 == l2 - r2);
    return multiply(
        power_mod(x, r1, m) * power_mod(y, r2, m) % m,
        sum_power(x * y % m, l1 - r1, m), 
        m
    );
}

ll sum_power2_general(ll x, ll y, ll l1, ll l2, ll r1, ll r2, ll m) {
    assert(l2 - r2 == r1 - l1);
    return multiply(
        power_mod(x, l1, m) * power_mod(y, r2, m) % m,
        sum_power2(x, y, r1 - l1, m), 
        m
    );
}

int main() {
    const ll MOD = 998244353;
    string s;

    ifstream input_file("string.txt");
    
    if (!input_file) {
        cerr << "Error: Unable to open input file!" << endl;
        return 1;
    }

    input_file >> s;
    input_file.close();

    ll n = s.length() - 1;
    // assert(n == 133232);
    
    ll answer = 0;
	
    for (int i = 1; i <= n; ++i) {
        ll d = s[i] - '0';

        // l = 1
        ll lsame1 = multiply(
            multiply(d, power_mod(2, n - i, MOD), MOD),
            power_mod(10, 2 * n - i, MOD),
            MOD
        );

        // l > 1
        ll lmore1 = i == 1 ? 0 : multiply(
            d,
            sum_power2_general(2, 10, n - i, 2 * n - (i + 1), n - 2, 2 * n - (2 * i - 1), MOD),
            MOD
        );

        ll original_add = add(lsame1, lmore1, MOD);
	    answer = add(answer, original_add, MOD);

        // r = n
        ll rsamen = multiply(
            multiply(d, power_mod(2, i - 1, MOD), MOD),
            power_mod(10, n - i, MOD),
            MOD
        );

        // r < n
        ll rlessn = i == n ? 0 : multiply(
            d,
            sum_power1_general(2, 10, n - 2, 2 * n - 2 * i, i - 1, n - i + 1, MOD),
            MOD
        );

        ll duplicate_add = add(rsamen, rlessn, MOD);
        answer = add(answer, duplicate_add, MOD);
    }

    cout << answer << "\n";
    return 0;
}
