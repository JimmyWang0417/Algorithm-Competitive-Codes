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
namespace comb
{
    vector<i64> fac, ifac, inv;
    auto init(int n)
    {
        fac.resize(n + 2), ifac.resize(n + 2), inv.resize(n + 2);
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i % mod;
        ifac[n] = quickpow(fac[n]);
        for (int i = n; i >= 1; --i)
            ifac[i - 1] = ifac[i] * i % mod;
        inv[1] = 1;
        for (int i = 2; i <= n; ++i)
            inv[i] = (-mod / i) * inv[mod % i] % mod;
    }
    auto A(int n, int m)
    {
        return fac[n] * ifac[n - m] % mod;
    }
    auto invA(int n, int m)
    {
        return ifac[n] * fac[n - m] % mod;
    }
    auto C(int n, int m)
    {
        return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
    }
    auto invC(int n, int m)
    {
        return ifac[n] * fac[m] % mod * fac[n - m] % mod;
    }
}
using namespace comb;
struct poly : vector<i64>
{
    constexpr static int inv2 = quickpow(2);
    constexpr static int inv3 = quickpow(3);
    using vector<i64>::vector;
    static inline vector<int> rk;
    static inline int limit, len;
    static auto init(size_t n)
    {
        limit = 1, len = 0;
        while (limit < (int)n)
        {
            limit <<= 1;
            ++len;
        }
        rk.resize(limit);
        for (int i = 0; i < limit; ++i)
            rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
    }
    auto friend &operator>>(istream &in, poly &rhs)
    {
        for (auto &i : rhs)
            in >> i;
        return in;
    }
    auto friend &operator<<(ostream &out, const poly &rhs)
    {
        for (auto i : rhs)
            out << (i + mod) % mod << ' ';
        return out;
    }
    auto NTT()
    {
        for (int i = 0; i < limit; ++i)
            if (i < rk[i])
                std::swap(at(i), at(rk[i]));
        for (int mid = 1; mid < limit; mid <<= 1)
        {
            const auto gn = quickpow(3, (mod - 1) / (mid << 1));
            for (int i = 0; i < limit; i += mid << 1)
            {
                i64 g = 1;
                for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
                {
                    auto x = at(i + j), y = at(i + j + mid) * g % mod;
                    at(i + j) = (x + y) % mod;
                    at(i + j + mid) = (x - y) % mod;
                }
            }
        }
    }
    auto INTT()
    {
        for (int i = 0; i < limit; ++i)
            if (i < rk[i])
                std::swap(at(i), at(rk[i]));
        for (int mid = 1; mid < limit; mid <<= 1)
        {
            const auto gn = quickpow(inv3, (mod - 1) / (mid << 1));
            for (int i = 0; i < limit; i += mid << 1)
            {
                i64 g = 1;
                for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
                {
                    auto x = at(i + j), y = at(i + j + mid) * g % mod;
                    at(i + j) = (x + y) % mod;
                    at(i + j + mid) = (x - y) % mod;
                }
            }
        }
        const auto invlimit = quickpow(limit);
        for (auto &i : (*this))
            (i *= invlimit) %= mod;
    }
    auto friend operator*(poly lhs, poly rhs)
    {
        if (lhs.empty() || rhs.empty())
            return poly{};
        auto up = lhs.size() + rhs.size() - 1;
        init(up);
        lhs.resize(limit), lhs.NTT();
        rhs.resize(limit), rhs.NTT();
        for (int i = 0; i < limit; ++i)
            (lhs[i] *= rhs[i]) %= mod;
        lhs.INTT(), lhs.resize(up);
        return lhs;
    }
    auto reverse() { ranges::reverse(*this); }
    auto friend operator^(poly lhs, poly rhs)
    {
        if (lhs.empty() || rhs.empty())
            return poly{};
        lhs = lhs * rhs;
        lhs.erase(lhs.begin(), lhs.begin() + rhs.size() - 1);
        return lhs;
    }
};
struct Main
{
    string s;
    char c;
    int n, m;
    int a, b;
    poly F;
    auto cdq(int l, int r)
    {
        if (l == r)
        {
            (F[l] += fac[a + 2 * l]) %= mod;
            return;
        }
        int mid = (l + r) >> 1;
        cdq(l, mid);
        poly G(F.begin() + l, F.begin() + mid + 1);
        poly H(r - l + 1);
        for (int i = 0; i < (int)G.size(); ++i)
            (G[i] *= ifac[l + i]) %= mod;
        for (int i = 0; i < (int)H.size(); ++i)
            H[i] = fac[2 * i] * ifac[i] % mod;
        G = G * H;
        for (int i = mid + 1; i <= r; ++i)
            (F[i] -= fac[i] * G[i - l]) %= mod;
        cdq(mid + 1, r);
    }
    Main()
    {
        cin >> s >> c;
        n = (int)s.length(), m = (int)ranges::count(s, c);
        a = 0, b = 0;
        for (int i = 0; i < n - i - 1; ++i)
        {
            if (s[i] == s[n - i - 1])
                b += (s[i] != c);
            else
                a += (s[i] != c) + (s[n - i - 1] != c);
        }
        if (!a)
        {
            cout << "0\n";
            return;
        }
        F.resize(b + 1);
        cdq(0, b);
        poly X(n + 1), Y(m + 1);
        for (int i = 1; i <= n; ++i)
            X[i] = invC(n, i) % mod;
        for (int i = 0; i <= m; ++i)
            Y[i] = C(m, i);
        auto Z = X ^ Y;
        i64 res = 0;
        for (int i = 0; i <= b; ++i)
        {
            int j = a + 2 * i;
            auto x = F[i] * C(b, i) % mod, y = Z[j] * ifac[j - 1] % mod;
            (res += x * y) %= mod;
        }
        if ((n & 1) && s[n / 2] != c)
        {
            for (int i = 0; i <= b; ++i)
            {
                int j = a + 2 * i + 1;
                auto x = F[i] * C(b, i) % mod * (j - 1) % mod, y = Z[j] * ifac[j - 1] % mod;
                (res += x * y) %= mod;
            }
        }
        cout << (res + mod) % mod << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init(5e6);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}

