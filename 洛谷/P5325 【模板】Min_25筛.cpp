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
constexpr int mod = 1e9 + 7;
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
template <typename T = i64>
struct min25
{
    i64 n;
    int block;
    vector<int> prime, id1, id2;
    vector<bool> vis;
    vector<i64> p;
    vector<T> coef;
    vector<vector<T>> pre, f;
    auto getid(i64 x) const
    {
        return x <= block ? id1[x] : id2[n / x];
    }
    template <typename F>
    auto sieve(F value)
    {
        for (int i = 2; i <= block; ++i)
        {
            if (!vis[i])
            {
                prime.emplace_back(i);
                for (int j = 0; j < (int)coef.size(); ++j)
                    pre[j].emplace_back((pre[j].back() + value(j, i)) % mod);
            }
            for (int j = 1; j < (int)prime.size(); ++j)
            {
                if (i * prime[j] > block)
                    break;
                vis[i * prime[j]] = true;
                if (i % prime[j] == 0)
                    break;
            }
        }
    }
    template <typename F>
    auto solve(i64 x, int y, F calcF) -> T
    {
        if (x <= 1 || x <= prime[y])
            return 0;
        int k = getid(x);
        T res = 0;
        for (int i = 0; i < (int)coef.size(); ++i)
            (res += coef[i] * (f[i][k] - pre[i][y])) %= mod;
        for (int i = y + 1; i < (int)prime.size() && (i64)prime[i] * prime[i] <= x; ++i)
        {
            i64 pe = prime[i];
            for (int e = 1; pe <= x; ++e)
            {
                (res += calcF(prime[i], e, pe) * (solve(x / pe, i, calcF) + (e > 1))) %= mod;
                if (pe > x / prime[i])
                    break;
                pe *= prime[i];
            }
        }
        return res;
    }
    template <typename F, typename G, typename H>
    auto calc(i64 _n, const vector<T> &_coef, F value, G prefix, H calcF)
    {
        if (!_n)
            return (T)0;
        n = _n, block = (int)sqrt(n), coef = _coef;
        prime.resize(1);
        id1.resize(block + 1), id2.resize(block + 1);
        vis.resize(block + 1);
        pre.resize(coef.size(), vector<T>(1));
        f.resize(coef.size());
        sieve(value);
        for (i64 l = 1, r; l <= n; l = r + 1)
        {
            i64 x = n / l;
            r = n / x;
            p.emplace_back(x);
            for (int i = 0; i < (int)coef.size(); ++i)
                f[i].emplace_back((prefix(i, x) - 1) % mod);
            if (x <= block)
                id1[x] = (int)p.size() - 1;
            else
                id2[n / x] = (int)p.size() - 1;
        }
        for (int i = 1; i < (int)prime.size(); ++i)
            for (int j = 0; j < (int)p.size() && (i64)prime[i] * prime[i] <= p[j]; ++j)
            {
                int k = getid(p[j] / prime[i]);
                for (int d = 0; d < (int)coef.size(); ++d)
                    (f[d][j] -= (pre[d][i] - pre[d][i - 1]) *
                                  (f[d][k] - pre[d][i - 1])) %= mod;
            }
        T answer = (solve(n, 0, calcF) + 1) % mod;
        return (answer + mod) % mod;
    }
};
struct Main
{
    i64 n;
    Main()
    {
        cin >> n;
        auto answer = min25().calc(
            n, vector<i64>{-1, 1},
            [](int k, i64 x)
            { return k ? x % mod * (x % mod) % mod : x % mod; },
            [](int k, i64 x)
            {
                if (!k)
                    return (i64)((i128)x * (x + 1) / 2 % mod);
                return (i64)((i128)x * (x + 1) * (2 * x + 1) / 6 % mod);
            },
            [](int, int, i64 pe)
            { return pe % mod * ((pe - 1) % mod) % mod; });
        cout << answer << '\n';
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
