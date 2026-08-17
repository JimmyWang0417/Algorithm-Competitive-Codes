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
    a %= mod;
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
vector<i64> fac, ifac, inv;
auto C(int n, int m)
{
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
struct Main
{
    int n, a, b;
    vector<int> p;
    auto dfs(int u, int v, int lea, int all) -> i64
    {
        if (!lea)
        {
            if (!((int)p.size() >= b && (p.empty() ? 0 : p.front()) >= a))
                return 0;
            auto q = p;
            for (auto &i : q)
                i *= 2;
            i64 res = fac[all];
            vector<int> r(q.empty() ? 0 : q.front());
            for (int i : q)
                for (int j = 0; j < i; ++j)
                    ++r[j];
            for (int i = 0; i < (int)q.size(); ++i)
                for (int j = 0; j < q[i]; ++j)
                    (res *= inv[(r[j] - i - 1) + (q[i] - j - 1) + 1]) %= mod;
            return res;
        }
        i64 res = 0;
        for (int i = 1; i <= v && i <= lea; ++i)
        {
            p.push_back(i);
            (res += dfs(u + 1, i, lea - i, all)) %= mod;
            p.pop_back();
        }
        return res;
    }
    Main()
    {
        cin >> n >> a >> b;
        inv.resize(n + 1), fac.resize(n + 1), ifac.resize(n + 1);
        inv[1] = 1;
        for (int i = 2; i <= n; ++i)
            inv[i] = (-mod / i) * inv[mod % i] % mod;
        fac[0] = 1;
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i % mod;
        ifac[n] = quickpow(fac[n]);
        for (int i = n; i >= 1; --i)
            ifac[i - 1] = ifac[i] * i % mod;
        i64 res = 0;
        for (int i = 0; i <= n / 2; ++i)
        {
            (res += dfs(0, i, i, 2 * i) * C(n, 2 * i)) %= mod;
            // cout << (dfs(0, i, i, 2 * i) + mod) % mod << ' ' << C(n, 2 * i) << '\n';
        }
        cout << (res + mod) % mod << '\n';
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

