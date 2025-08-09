#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 4e5 + 5;
constexpr int mod = 998244353;
constexpr auto quickpow(ll a, int b = mod - 2)
{
    ll res = 1;
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
{
    constexpr int inv3 = quickpow(3);
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
        vector<ll> dp;
        poly(int _n = 0) { dp.resize(_n); }
        poly(vector<ll> _dp) { dp = _dp; }

        auto size() const { return (int)dp.size(); }
        auto resize(int _n) { dp.resize(_n); }

        auto operator[](const int &x) const { return dp[x]; }
        auto &operator[](const int &x) { return dp[x]; }

        auto friend &operator>>(istream &lhs, poly &rhs)
        {
            for (auto &i : rhs.dp)
                lhs >> i;
            return lhs;
        }
        auto friend &operator<<(ostream &lhs, const poly &rhs)
        {
            for (auto i : rhs.dp)
                lhs << (i + mod) % mod << ' ';
            return lhs;
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

        auto NTT()
        {
            for (int i = 0; i < limit; ++i)
                if (i < rk[i])
                    swap(dp[i], dp[rk[i]]);
            for (int mid = 1; mid < limit; mid <<= 1)
            {
                ll gn = quickpow(3, (mod - 1) / (mid << 1));
                for (int i = 0; i < limit; i += mid << 1)
                {
                    ll g = 1;
                    for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
                    {
                        ll x = dp[i + j], y = dp[i + j + mid] * g % mod;
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
                ll gn = quickpow(inv3, (mod - 1) / (mid << 1));
                for (int i = 0; i < limit; i += mid << 1)
                {
                    ll g = 1;
                    for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
                    {
                        ll x = dp[i + j], y = dp[i + j + mid] * g % mod;
                        dp[i + j] = (x + y) % mod;
                        dp[i + j + mid] = (x - y) % mod;
                    }
                }
            }
            ll inv = quickpow(limit);
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
            res.INTT();
            res.resize(up);
            return res;
        }
        auto inv(int n) const
        {
            if (n == 1)
                return poly(vector<ll>{quickpow(dp[0])});
            poly F = inv((n + 1) / 2), G(vector<ll>(dp.begin(), dp.begin() + n));
            init(n * 2);
            F.resize(limit), G.resize(limit);
            F.NTT(), G.NTT();
            for (int i = 0; i < limit; ++i)
                F[i] = (2 - F[i] * G[i] % mod) * F[i] % mod;
            F.INTT();
            F.resize(n);
            return F;
        }
        auto inv() const { return inv(size()); }
        auto reverse() { std::reverse(dp.begin(), dp.end()); }

        auto friend operator/(poly lhs, poly rhs)
        {
            lhs.reverse(), rhs.reverse();
            int up = lhs.size() - rhs.size() + 1;
            lhs.resize(up), rhs.resize(up);
            auto res = lhs * rhs.inv();
            res.resize(up);
            res.reverse();
            return res;
        }
        auto friend operator%(poly lhs, poly rhs)
        {
            auto res = lhs - lhs / rhs * rhs;
            res.resize(rhs.size() - 1);
            return res;
        }
    };
}
using polynomial::poly;
auto _main()
{
    int n, m;
    cin >> n >> m;
    poly a(n + 1), b(m + 1);
    cin >> a >> b;
    cout << a / b << '\n'
         << a % b << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas)
        _main();
    return 0;
}