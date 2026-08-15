#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
auto quickpow(i64 a, int b)
{
    i64 res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
struct Main
{
    int n;
    vector<i64> fac, ifac;
    vector<i64> sum;
    Main()
    {
        cin >> n;
        fac.resize(n + 5), ifac.resize(n + 5);
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i % mod;
        ifac[n] = quickpow(fac[n], mod - 2);
        for (int i = n; i >= 1; --i)
            ifac[i - 1] = ifac[i] * i % mod;
        auto C = [&](int _n, int _m)
        {
            return fac[_n] * ifac[_m] % mod * ifac[_n - _m] % mod;
        };
        sum.resize(2 * n + 5);
        for (int i = 0; i <= n; ++i)
            sum[i * 2] = C(n, i);
        partial_sum(sum.begin(), sum.end(), sum.begin());
        auto calc = [&](int l, int r) -> i64
        {
            i64 res = sum[min(r, 2 * n)];
            if (l > 0)
                (res -= sum[l - 1]) %= mod;
            return res;
        };
        i64 lasans = 0;
        for (int k = 0; k <= n; ++k)
        {
            i64 res = 0;
            for (int i = -k - 1, j = k, v = 1; i <= n; i += 2 * k + 3, j += 2 * k + 3, v = -v)
                (res += v * calc(i + n, j + n)) %= mod;
            for (int i = -3 * k - 4, j = -k - 3, v = -1; j >= -n; i -= 2 * k + 3, j -= 2 * k + 3, v = -v)
                (res += v * calc(i + n, j + n)) %= mod;
            cout << ((res - lasans) % mod + mod) % mod << ' ';
            lasans = res;
        }
        cout << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}

