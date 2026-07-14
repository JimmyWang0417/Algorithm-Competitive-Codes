#include <bit>
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
constexpr int inv2 = quickpow(2);
constexpr int N = 19;
struct Main
{
    int n, m;
    vector<i64> d;
    vector<i64> CCF;
    auto insert(i64 x)
    {
        for (int i = m - 1; i >= 0; --i)
            if ((x >> i) & 1)
            {
                if (!d[i])
                {
                    d[i] = x;
                    return true;
                }
                x ^= d[i];
            }
        return false;
    }
    vector<int> cnt;
    auto dfs(int u, i64 v) -> void
    {
        if (u == -1)
        {
            cnt[popcount((u64)v)]++;
            return;
        }
        dfs(u - 1, v);
        dfs(u - 1, v ^ CCF[u]);
    }
    Main()
    {
        cin >> n >> m;
        d.resize(m);
        int k = 0;
        for (int i = 0; i < n; ++i)
        {
            i64 x;
            cin >> x;
            k += insert(x);
        }
        cnt.resize(m + 1);
        if (k <= 26)
        {
            for (int i = 0; i < m; ++i)
                if (d[i])
                    CCF.push_back(d[i]);
            dfs((int)CCF.size() - 1, 0);
            auto times = quickpow(2, n - k);
            for (int i = 0; i <= m; ++i)
                cout << cnt[i] * times % mod << ' ';
            cout << '\n';
        }
        else
        {
            vector<i64> e(m);
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < i; ++j)
                    if ((d[i] >> j) & 1)
                        d[i] ^= d[j];
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < m; ++j)
                    if ((d[i] >> j) & 1)
                        e[j] |= 1ll << i;
            for (int i = 0; i < m; ++i)
                e[i] ^= 1ll << i;
            for (int i = 0; i < m; ++i)
                if (e[i])
                    CCF.push_back(e[i]);
            dfs((int)CCF.size() - 1, 0);
            vector<vector<int>> C(m + 1, vector<int>(m + 1));
            for (int i = C[0][0] = 1; i <= m; ++i)
                for (int j = C[i][0] = 1; j <= i; ++j)
                    C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
            auto times = quickpow(2, n - m + mod - 1) % mod;
            for (int c = 0; c <= m; ++c)
            {
                i64 res = 0;
                for (int _d = 0; _d <= m; ++_d)
                    for (int i = 0; i <= c && i <= _d; ++i)
                        (res += (i & 1 ? -1ll : 1ll) * cnt[_d] * C[_d][i] % mod * C[m - _d][c - i]) %= mod;
                cout << (res * times % mod + mod) % mod << ' ';
            }
            cout << '\n';
        }
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