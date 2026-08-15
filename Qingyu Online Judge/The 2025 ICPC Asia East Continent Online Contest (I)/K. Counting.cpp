#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float128 f128;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
constexpr auto quickpow(i64 a, int b = mod - 2)
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
constexpr auto inv2 = quickpow(2);
constexpr auto inv3 = quickpow(3);
namespace comb
{
    vector<i64> fac, ifac;
    auto init(int n)
    {
        fac.resize(n), ifac.resize(n);
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i % mod;
        ifac[n] = quickpow(fac[n]);
        for (int i = n; i >= 1; --i)
            ifac[i - 1] = ifac[i] * i % mod;
    }
    auto C(int n, int m) -> i64
    {
        if (m < 0 || n < m)
            return 0;
        return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
    }
    auto A(int n, int m) -> i64
    {
        if (m < 0 || n < m)
            return 0;
        return fac[n] * ifac[n - m] % mod;
    }
}
namespace polynomial
{
    vector<int> rk;
    int len, limit;
    auto init(int n)
    {
        len = 0, limit = 1;
        while (limit < n)
        {
            limit <<= 1;
            ++len;
        }
        rk.resize(limit);
        for (int i = 0; i < limit; ++i)
            rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
    }
    struct poly
    {
        vector<i64> dp;
        poly(int n) : dp(n) {}
        poly(const vector<i64> &_dp) : dp(_dp) {}
        auto size() { return (int)dp.size(); }
        auto resize(int n) { dp.resize(n); }
        auto &operator[](int x) { return dp[x]; }
        const auto &operator[](int x) const { return dp[x]; }
        auto NTT()
        {
            for (int i = 0; i < limit; ++i)
                if (i < rk[i])
                    swap(dp[i], dp[rk[i]]);
            for (int mid = 1; mid < limit; mid <<= 1)
            {
                const auto gn = quickpow(3, (mod - 1) / (mid << 1));
                for (int i = 0; i < limit; i += mid << 1)
                {
                    i64 g = 1;
                    for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
                    {
                        auto x = dp[i + j], y = dp[i + j + mid] * g % mod;
                        dp[i + j] = (x + y) % mod;
                        dp[i + j + mid] = (x - y) % mod;
                    }
                }
            }
        }
        auto INTT()
        {
            for (int i = 0; i < limit; ++i)
                if (i < rk[i])
                    swap(dp[i], dp[rk[i]]);
            for (int mid = 1; mid < limit; mid <<= 1)
            {
                const auto gn = quickpow(inv3, (mod - 1) / (mid << 1));
                for (int i = 0; i < limit; i += mid << 1)
                {
                    i64 g = 1;
                    for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
                    {
                        auto x = dp[i + j], y = dp[i + j + mid] * g % mod;
                        dp[i + j] = (x + y) % mod;
                        dp[i + j + mid] = (x - y) % mod;
                    }
                }
            }
            auto inv = quickpow(limit);
            for (int i = 0; i < limit; ++i)
                (dp[i] *= inv) %= mod;
        }
        auto friend operator*(poly lhs, poly rhs)
        {
            int up = lhs.size() + rhs.size() - 1;
            init(up);
            lhs.resize(limit), rhs.resize(limit);
            lhs.NTT(), rhs.NTT();
            poly res(limit);
            for (int i = 0; i < limit; ++i)
                res[i] = lhs[i] * rhs[i] % mod;
            res.INTT(), res.resize(up);
            return res;
        }
    };
}
using namespace comb;
using polynomial::poly;
auto _main()
{
    comb::init(1e6);
    int n, q;
    cin >> n >> q;
    auto invn = ifac[n] * fac[n - 1] % mod;
    vector<vector<i64>> answer(n + 5);
    {
        answer[0].resize(n + 1);
        if (n == 1)
            answer[0][1] = 1;
        else
        {
            for (int m = 1; m < n; ++m)
                answer[0][m] = C(n, m) * C(n - 2, m - 1) % mod * invn % mod;
        }
    }
    for (int k = 1; k <= n; ++k)
    {
        int m = (n - 1) / k;
        answer[k].resize(m + 1);
        poly a(m + 1), b(m + 1);
        for (int i = 0; i <= m; ++i)
        {
            a[i] = invn * C(n, i) % mod * C((n - k * i - 1) + (n - i - 1), n - i - 1) % mod * fac[i] % mod;
            b[m - i] = (i & 1 ? -1 : 1) * ifac[i];
        }
        poly c = a * b;
        for (int i = 0; i <= m; ++i)
            answer[k][i] = c[i + m] * ifac[i] % mod;
    }
    while (q--)
    {
        int m, k;
        cin >> m >> k;
        if (m < (int)answer[k].size())
            cout << (answer[k][m] + mod) % mod << '\n';
        else
            cout << 0 << '\n';
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init(N - 5);
    int T = 1;
    // cin >> T;
    while (T--)
        _main();
    return 0;
}
