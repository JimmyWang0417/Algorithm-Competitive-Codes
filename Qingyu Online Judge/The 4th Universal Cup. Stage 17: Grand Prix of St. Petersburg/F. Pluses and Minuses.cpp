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
    vector<i64> fac, ifac;
    auto init(int n)
    {
        fac.resize(n + 1);
        ifac.resize(n + 1);
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i % mod;
        ifac[n] = quickpow(fac[n]);
        for (int i = n; i >= 1; --i)
            ifac[i - 1] = ifac[i] * i % mod;
    }
    auto C(int n, int m)
    {
        return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
    }
}
using namespace comb;
struct poly : vector<i64>
{
    constexpr static int inv3 = quickpow(3);
    static inline int len, limit;
    static inline vector<int> rk;
    static auto init(size_t n)
    {
        len = 0, limit = 1;
        while (limit < (int)n)
        {
            ++len;
            limit <<= 1;
        }
        rk.resize(limit);
        for (int i = 0; i < limit; ++i)
            rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
    }
    using vector<i64>::vector;
    int low = 0;
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
        auto invlimit = quickpow(limit);
        for (auto &i : *this)
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
        lhs.low += rhs.low;
        for (int i = 0; i < limit; ++i)
            (lhs[i] *= rhs[i]) %= mod;
        lhs.INTT(), lhs.resize(up);
        return lhs;
    }
};
struct Main
{
    int n, m;
    vector<bool> p;
    auto window(int t, int radius) -> pair<int, int>
    {
        int low = max(0, (t - radius + 1) >> 1);
        int high = min(t, (t + radius) >> 1);
        return {low, high};
    }
    auto cut(const poly &f, int t, int radius)
    {
        auto [low, high] = window(t, radius);
        poly g;
        g.low = low;
        if (low > high || f.empty())
            return g;
        g.resize(high - low + 1);
        for (int i = low; i <= high; ++i)
            if (f.low <= i && i < f.low + (int)f.size())
                g[i - low] = f[i - f.low];
        return g;
    }
    auto advance(const poly &f, int l, int mid, int radius)
    {
        auto [low, high] = window(mid, radius);
        poly g;
        g.low = low;
        if (low > high)
            return g;
        int d = mid - l;
        g.resize(high - low + 1);
        {
            poly h(d + 1);
            for (int i = 0; i <= d; ++i)
                h[i] = fac[d] * ifac[i] % mod * ifac[d - i] % mod;
            h = f * h;
            for (int i = low; i <= high; ++i)
                if (h.low <= i && i < h.low + (int)h.size())
                    g[i - g.low] += h[i - h.low];
        }
        {
            poly a(d), b(d);
            for (int i = 0; i < d; ++i)
            {
                a[d - 1 - i] = p[mid - i - 1] * fac[i];
                b[i] = ifac[i];
            }
            auto c = a * b;
            for (int i = max(low, 1); i <= min(high, d); i++)
                (g[i - low] += ifac[i - 1] * c[d - i]) %= mod;
        }
        return g;
    }
    vector<i64> answer;
    auto cdq(const poly &f, int l, int r)
    {
        if (r - l == 1)
        {
            if (r % 2 == 0)
            {
                poly g = advance(f, l, r, 0);
                answer[r / 2] = g.empty() ? 0 : g[0];
            }
            return;
        }
        int mid = (l + r) / 2;
        cdq(cut(f, l, mid - l), l, mid);
        cdq(advance(f, l, mid, r - mid), mid, r);
    }
    Main()
    {
        cin >> n >> m;
        p.resize(2 * n + 5);
        for (int i = 1; i <= m; ++i)
        {
            int x;
            cin >> x;
            p[x] = true;
        }
        answer.resize(n + 1);
        cdq({}, 0, 2 * n);
        for (int i = 1; i <= n; ++i)
            cout << (answer[i] + mod) % mod << '\n';
    }
};
signed main()
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
