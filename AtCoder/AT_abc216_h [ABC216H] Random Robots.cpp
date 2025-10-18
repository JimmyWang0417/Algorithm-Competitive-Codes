#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
constexpr auto quickpow(i64 a, int b)
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
constexpr auto inv2 = quickpow(2, mod - 2);
struct Comb
{
    vector<i64> _fac, _ifac, _inv;
    auto init(int n)
    {
        int m = (int)_fac.size() - 1;
        if (n <= m)
            return;
        _fac.resize(n + 1), _ifac.resize(n + 1), _inv.resize(n + 1);
        for (int i = m + 1; i <= n; ++i)
        {
            _fac[i] = _fac[i - 1] * i % mod;
            _inv[i] = -mod / i * _inv[mod % i] % mod;
            _ifac[i] = _ifac[i - 1] * _inv[i] % mod;
        }
    }
    auto fac(int n)
    {
        init(n);
        return _fac[n];
    }
    auto ifac(int n)
    {
        init(n);
        return _fac[n];
    }
    auto inv(int n)
    {
        init(n);
        return _inv[n];
    }
    auto C(int n, int m) -> i64
    {
        if (m < 0 || n < m)
            return 0;
        init(n);
        return _fac[n] * _ifac[m] % mod * _ifac[n - m] % mod;
    }
    auto A(int n, int m) -> i64
    {
        if (m < 0 || n < m)
            return 0;
        init(n);
        return _fac[n] * _ifac[n - m] % mod;
    }
    Comb(int n = 0) : _fac({1, 1}), _ifac({1, 1}), _inv({0, 1}) { init(n); }
} comb;
struct Main
{
    Main()
    {
        int n, m, k;
        cin >> k >> n;
        vector<int> a(k);
        for (int &i : a)
        {
            cin >> i;
            ++i;
        }
        m = *max_element(a.begin(), a.end());
        vector dp(n + m + 1, vector<i64>(1 << k));
        vector cnt(1 << k, vector<bool>(k));
        for (int S = 0; S < (1 << k); ++S)
            for (int i = k - 1, j = 0; i >= 0; --i)
            {
                if ((S >> i) & 1)
                    ++j;
                else
                    cnt[S][i] = j & 1;
            }

        dp[0][0] = 1;
        for (int i = 1; i <= n + m; ++i)
        {
            for (int S = 0; S < (1 << k); ++S)
            {
                (dp[i][S] += dp[i - 1][S]) %= mod;
                for (int j = 0; j < k && a[j] <= i; ++j)
                {
                    if ((S >> j) & 1)
                        continue;
                    (dp[i][S | (1 << j)] += (cnt[S][j] ? -1 : 1) * comb.C(n, i - a[j]) * dp[i - 1][S]) %= mod;
                }
            }
        }
        cout << (dp[n + m][(1 << k) - 1] + mod) % mod * quickpow(inv2, n * k) % mod;
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