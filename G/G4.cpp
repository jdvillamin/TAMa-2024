#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// Modular exponentiation: (b^e) % m
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

// Modular multiplication: (a * b) % m
ll multiply(ll a, ll b, ll m) {
    return ((a % m) * (b % m)) % m;
}

// Modular addition: (a + b) % m
ll add(ll a, ll b, ll m) {
    return ((a % m) + (b % m)) % m;
}

// Compute x^n + x^(n - 1) + ... + 1 using recursion.
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

// Compute x^n + x^(n - 1) * y + ... + x * y^(n - 1) + y^n recursively.
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

// General sum function 1: Uses sum_power2.
ll sum_power1_general(ll x, ll y, ll l1, ll l2, ll r1, ll r2, ll m) {
    assert(l1 - r1 == l2 - r2);
    return multiply(
        power_mod(x, r1, m) * power_mod(y, r2, m) % m,
        sum_power(x * y % m, l1 - r1, m), 
        m
    );
}

// General sum function 2: Uses sum_power2.
ll sum_power2_general(ll x, ll y, ll l1, ll l2, ll r1, ll r2, ll m) {
    assert(l2 - r2 == r1 - l1);
    return multiply(
        power_mod(x, l1, m) * power_mod(y, r2, m) % m,
        sum_power2(x, y, r1 - l1, m), 
        m
    );
}

int main() {
    const ll MOD = 998244353;  // Use a large prime modulus
    for (ll x = 1; x <= 10; x++)
	    cout << sum_power(2, x, MOD) << " \n"[x == 10];
    for (ll x = 1; x <= 10; x++)
	    cout << sum_power2(2, 3, x, MOD) << " \n"[x == 10];
    string s;  // Input string representing the digits

    // Read input from the file "string.txt"
    ifstream input_file("string.txt");
    
    if (!input_file) {
        cerr << "Error: Unable to open input file!" << endl;
        return 1;
    }

    input_file >> s;
    input_file.close();

    cout << s << "\n";
  
    ll n = s.length() - 1;
    // assert(n == 133232);
    
    ll answer = 0;
	
    // Compute the final answer iteratively
    for (int i = 1; i <= n; ++i) {
        ll d = s[i] - '0';  // Convert character to integer
        
	// Case: l = 1
        ll lsame1 = multiply(
            multiply(d, power_mod(2, n - i, MOD), MOD),
            power_mod(10, 2 * n - i, MOD),
            MOD
        );

        // Case: l > 1
        ll lmore1 = i == 1 ? 0 : multiply(
            d,
            sum_power2_general(2, 10, n - i, 2 * n - (i + 1), n - 2, 2 * n - (2 * i - 1), MOD),
            MOD
        );

        ll original_add = add(lsame1, lmore1, MOD);
        cout << "Original add: " << original_add << "\n";
	answer = add(answer, original_add, MOD);

        // Case: r = n
        ll rsamen = multiply(
            multiply(d, power_mod(2, i - 1, MOD), MOD),
            power_mod(10, n - i, MOD),
            MOD
        );

        // Case: r < n
        ll rlessn = i == n ? 0 : multiply(
            d,
            sum_power1_general(2, 10, n - 2, 2 * n - 2 * i, i - 1, n - i + 1, MOD),
            MOD
        );

        ll duplicate_add = add(rsamen, rlessn, MOD);
	cout << "Duplicate add: " << duplicate_add << "\n";
        answer = add(answer, duplicate_add, MOD);
    }

    cout << answer << "\n";
    return 0;
}
