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
constexpr auto inv3 = quickpow(3, mod - 2);
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
    poly(const initializer_list<i64> &_dp) : dp(_dp) {}

    auto size() { return (int)dp.size(); }
    auto resize(size_t n) { return dp.resize(n); }

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

        auto invlimit = quickpow(limit, mod - 2);
        for (int i = 0; i < limit; ++i)
            (dp[i] *= invlimit) %= mod;
    }
    auto friend operator*(poly lhs, poly rhs)
    {
        int up = lhs.size() + rhs.size() - 1;
        init(up);
        lhs.resize(limit), lhs.NTT();
        rhs.resize(limit), rhs.NTT();
        for (int i = 0; i < limit; ++i)
            (lhs[i] *= rhs[i]) %= mod;
        lhs.INTT(), lhs.resize(up);
        return lhs;
    }
    auto friend &operator<<(ostream &out, const poly &rhs)
    {
        for (auto i : rhs.dp)
            out << (i + mod) % mod << ' ';
        return out;
    }
};
struct comb
{
    vector<i64> fac, ifac;
    comb(int n) : fac(n + 1), ifac(n + 1)
    {
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i % mod;
        ifac[n] = quickpow(fac[n], mod - 2);
        for (int i = n; i >= 1; --i)
            ifac[i - 1] = ifac[i] * i % mod;
    }
    auto C(int n, int m) -> i64
    {
        if (n < 0 || n < m)
            return 0;
        return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
    }
} comb(1e6);
struct Main
{
    int n;
    vector<pair<int, int>> a;
    Main()
    {
        cin >> n;
        a.resize(n);
        for (auto &[x, y] : a)
            cin >> x >> y;
        poly X1(n), X2(2 * n), Y1(n), Y2(2 * n);
        for (int i = 0; i < n; ++i)
        {
            X1[i] = a[n - i - 1].first;
            Y1[i] = a[n - i - 1].second;
            X2[i] = X2[i + n] = a[i].first;
            Y2[i] = Y2[i + n] = a[i].second;
        }
        auto A = X1 * Y2;
        auto B = X2 * Y1;
        // cerr << A << '\n' << B << '\n';
        poly C(n + 1), D(n + 1);
        for (int i = 2; i < n; ++i)
            C[n - i] = (A[n - 1 + (i - 1)] - B[n - 1 + (i - 1)]) * comb.fac[n - i] % mod;
        for (int i = 0; i <= n; ++i)
            D[i] = comb.ifac[n - i] % mod;
        poly E = C * D;
        for (int i = 1; i <= n - 2; ++i)
            cout << (E[n + i] * comb.ifac[i] % mod + mod) % mod << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
