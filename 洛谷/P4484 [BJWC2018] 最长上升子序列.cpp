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
struct Main
{
    int n;
    vector<i64> inv, fac, ifac;
    vector<int> a, b;
    i64 answer;
    auto dfs(int u, int v, int lea)
    {
        if (!lea)
        {
            auto d = [&]()
            {
                auto res = fac[n];
                for (int i = 0; i < u; ++i)
                    for (int j = 0; j < a[i]; ++j)
                        (res *= inv[(b[j] - i - 1) + (a[i] - j - 1) + 1]) %= mod;
                return res;
            }();
            (answer += d * d % mod * a.front()) %= mod;
            return;
        }
        for (int i = 1; i <= v && i <= lea; ++i)
        {
            a[u] = i;
            ++b[i - 1];
            dfs(u + 1, i, lea - i);
        }
        for (int i = 1; i <= v && i <= lea; ++i)
            --b[i - 1];
    }
    Main() : answer(0)
    {
        cin >> n;
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
        a.resize(n), b.resize(n);
        dfs(0, n, n);
        cout << (answer * ifac[n] % mod + mod) % mod << '\n';
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
