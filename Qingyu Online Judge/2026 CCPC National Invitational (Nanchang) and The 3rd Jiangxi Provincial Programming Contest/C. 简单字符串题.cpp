#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr int mod = 998244353;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
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
{
    struct poly : vector<i64>
    {
        constexpr static bool has = false;

        constexpr static int inv2 = quickpow(2);
        constexpr static int inv3 = quickpow(3);
        constexpr static int imagUnit = 86583718;

        inline static vector<int> rk;
        inline static int len, limit;
        static auto init(int n)
        {
            len = 0, limit = 1;
            while (limit < n)
            {
                ++len;
                limit <<= 1;
            }
            rk.resize(limit);
            for (int i = 0; i < limit; ++i)
                rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
        }

        using vector<i64>::vector;

        auto NTT()
        {
            auto &dp = (*this);
            for (int i = 0; i < limit; ++i)
                if (i < rk[i])
                    std::swap(dp[i], dp[rk[i]]);
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
            auto &dp = (*this);
            for (int i = 0; i < limit; ++i)
                if (i < rk[i])
                    std::swap(dp[i], dp[rk[i]]);
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
        auto reverse() { std::reverse(begin(), end()); }
        auto fit(size_t n, i64 value = 0) const
        {
            auto res = *this;
            res.resize(n, value);
            return res;
        }

        auto friend operator*(poly lhs, poly rhs)
        {
            if (lhs.empty() || rhs.empty())
                return poly{};

            auto up = lhs.size() + rhs.size() - 1;
            constexpr static size_t LIM = 128;
            if (lhs.size() <= LIM || rhs.size() <= LIM)
            {
                poly res(up);
                for (int i = 0; i < (int)lhs.size(); ++i)
                    for (int j = 0; j < (int)rhs.size(); ++j)
                        (res[i + j] += lhs[i] * rhs[j]) %= mod;
                return res;
            }

            init((int)up);
            lhs.resize(limit), lhs.NTT();
            rhs.resize(limit), rhs.NTT();
            poly res(limit);
            for (int i = 0; i < limit; ++i)
                res[i] = lhs[i] * rhs[i] % mod;
            res.INTT(), res.resize(up);
            return res;
        }
    };
}
using namespace polynomial;

struct kmp
{
    string s;
    vector<int> p;
    kmp() = default;
    kmp(const string &_s) : s(_s), p(_s.size())
    {
        for (int i = 1, j = 0; i < (int)p.size(); ++i)
        {
            while (j && s[i] != s[j])
                j = p[j - 1];
            if (s[i] == s[j])
                ++j;
            p[i] = j;
        }
    }
};
namespace comb
{
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
    auto C(int n, int m) -> i64
    {
        if (n < 0 || n < m)
            return 0;
        return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
    }
}
using namespace comb;
struct Main
{
    int n, m;
    string s, t;
    vector<int> d;
    Main()
    {
        cin >> n >> m;
        cin >> s;
        t = s;
        reverse(t.begin(), t.end());
        kmp p(s), q(t);
        d.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            for (int j = i; j <= n; j += i)
                d[j]++;
        poly a(n + 1), b(n + 1);
        for (int i = 0; i < n; ++i)
        {
            if ((i + 1) % (i + 1 - p.p[i]) == 0)
                a[i + 1] = d[(i + 1) / (i + 1 - p.p[i])];
            else
                a[i + 1] = 1;
            if ((i + 1) % (i + 1 - q.p[i]) == 0)
                b[i + 1] = d[(i + 1) / (i + 1 - q.p[i])];
            else
                b[i + 1] = 1;
        }
        auto c = a * b;
        if (m == 0)
        {
            cout << (c[n] + mod) % mod << '\n';
            return;
        }
        // for (int i = 1; i <= n; ++i)
        //     cout << a[i] << ' ';
        // cout << '\n';
        // for (int i = 1; i <= n; ++i)
        //     cout << b[i] << ' ';
        // cout << '\n';
        // for (int i = 1; i <= n; ++i)
        //     cout << c[i] << ' ';
        // cout << '\n';
        i64 res = 0;
        for (int i = 1; i <= n; ++i)
            (res += C(n - i - 1, m - 1) * c[i]) %= mod;
        cout << (res + mod) % mod << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init(5e5);
    int T = 1;
    while (T--)
        Main();
    return 0;
}