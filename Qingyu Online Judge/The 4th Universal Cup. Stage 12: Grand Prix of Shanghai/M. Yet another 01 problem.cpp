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
namespace polynomial
{ // NTT模数 998244353, 1004535809, 4179340454199820289
    constexpr int inv2 = quickpow(2);
    constexpr int inv3 = quickpow(3);
    constexpr int imagUnit = 86583718;
    int limit, len;
    vector<int> rk;
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
        poly() = default;
        poly(int _n) : dp(_n) {}
        poly(const initializer_list<i64> &_dp) : dp(_dp) {}
        poly(const vector<i64> &_dp) : dp(_dp) {}

        auto size() const { return (int)dp.size(); }
        auto resize(int _n) { dp.resize(_n); }

        auto &operator[](int x) { return dp[x]; }
        const auto &operator[](int x) const { return dp[x]; }

        auto friend &operator>>(istream &in, poly &p)
        {
            for (auto &i : p.dp)
                in >> i;
            return in;
        }
        auto friend &operator<<(ostream &out, const poly &p)
        {
            for (auto i : p.dp)
                out << (i + mod) % mod << ' ';
            return out;
        }

        auto friend operator+(poly lhs, poly rhs)
        {
            poly res(max(lhs.size(), rhs.size()));
            lhs.resize(res.size()), rhs.resize(res.size());
            for (int i = 0; i < res.size(); ++i)
                res[i] = (lhs[i] + rhs[i]) % mod;
            return res;
        }
        auto friend operator-(poly lhs, poly rhs)
        {
            poly res(max(lhs.size(), rhs.size()));
            lhs.resize(res.size()), rhs.resize(res.size());
            for (int i = 0; i < res.size(); ++i)
                res[i] = (lhs[i] - rhs[i]) % mod;
            return res;
        }
        auto friend operator*(poly res, i64 rhs)
        {
            for (auto &i : res.dp)
                (i *= rhs) %= mod;
            return res;
        }
        auto friend operator/(poly res, i64 rhs)
        {
            return res * quickpow(rhs);
        }

        auto NTT()
        {
            for (int i = 0; i < limit; ++i)
                if (i < rk[i])
                    swap(dp[i], dp[rk[i]]);
            for (int mid = 1; mid < limit; mid <<= 1)
            {
                i64 gn = quickpow(3, (mod - 1) / (mid << 1));
                for (int i = 0; i < limit; i += mid << 1)
                {
                    i64 g = 1;
                    for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
                    {
                        i64 x = dp[i + j], y = dp[i + j + mid] * g % mod;
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
                i64 gn = quickpow(inv3, (mod - 1) / (mid << 1));
                for (int i = 0; i < limit; i += mid << 1)
                {
                    i64 g = 1;
                    for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
                    {
                        i64 x = dp[i + j], y = dp[i + j + mid] * g % mod;
                        dp[i + j] = (x + y) % mod;
                        dp[i + j + mid] = (x - y) % mod;
                    }
                }
            }
            i64 inv = quickpow(limit);
            for (int i = 0; i < limit; ++i)
                (dp[i] *= inv) %= mod;
        }

        // 多项式乘法
        auto friend operator*(poly lhs, poly rhs)
        {
            int up = lhs.size() + rhs.size() - 1;
            init(up);
            lhs.resize(limit), rhs.resize(limit);
            lhs.NTT(), rhs.NTT();
            poly res(limit);
            for (int i = 0; i < limit; ++i)
                res[i] = lhs[i] * rhs[i] % mod;
            res.INTT();
            res.resize(up);
            return res;
        }
    };
}
using polynomial::poly;
using polynomial::inv2;
vector<i64> fac, ifac;
auto init(int n)
{
    fac.resize(n + 1), ifac.resize(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n]);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
}
auto catalan(int n)
{
    return ifac[n] * ifac[n + 1] % mod * fac[2 * n] % mod;
}
struct matrix
{
    poly g[2][2];
    matrix() = default;
    auto &operator[](int x) { return g[x]; }
    const auto &operator[](int x) const { return g[x]; }
    auto operator*(const matrix &rhs) const
    {
        matrix res;
        for (int i = 0; i < 2; ++i)
            for (int k = 0; k < 2; ++k)
                for (int j = 0; j < 2; ++j)
                    res[i][j] = res[i][j] + g[i][k] * rhs[k][j];
        return res;
    }
};
struct Main
{
    int n;
    string s;
    auto solve(int l, int r)
    {
        if (l == r)
        {
            matrix res;
            res[0][0] = {1};
            res[0][1] = {0, s[l] != s[l - 1] ? 1 : -1};
            res[1][0] = {1};
            res[1][1] = {0};
            return res;
        }
        int mid = (l + r) >> 1;
        return solve(l, mid) * solve(mid + 1, r);
    }
    Main()
    {
        cin >> n >> s;
        if (n == 1)
        {
            cout << (s.front() == '0') << '\n';
            return;
        }
        auto _ = solve(1, n - 1);
        auto res = _[0][0] + _[0][1];
        i64 ans = 0;
        for (int i = 0; i < (int)res.size(); ++i)
            (ans += catalan(n - 1 - i) * res[i]) %= mod;
        cout << (ans * inv2 % mod + mod) % mod << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init(1e6);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}

