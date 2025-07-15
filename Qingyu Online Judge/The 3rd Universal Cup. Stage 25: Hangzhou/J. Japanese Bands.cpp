#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
constexpr int mod = 1e9 + 7;
constexpr int N = (1 << 20) + 5;
ll inv[23];
inline ll C(int n, int m)
{
    if (n < 0 || n < m)
        return 0;
    ll ans = 1;
    for (int i = 1; i <= m; ++i)
        (ans *= (n - i + 1) * inv[i] % mod) %= mod;
    return ans;
}
pair<int, int> a[N];
ll f[N], g[N];
int need[N];
int p[N], tot;
inline void _main()
{
    int n1, n2, m, k;
    cin >> n1 >> n2 >> m >> k;
    for (int i = 1; i <= k; ++i)
    {
        auto &[x, y] = a[i];
        cin >> x >> y;
        p[tot++] = x, p[tot++] = y;
    }
    sort(p, p + tot);
    tot = (int)(unique(p, p + tot) - p);
    for (int i = 1; i <= k; ++i)
    {
        auto [x, y] = a[i];
        x = (int)(lower_bound(p, p + tot, x) - p);
        y = (int)(lower_bound(p, p + tot, y) - p);
        need[x] |= 1 << y;
        need[y] |= 1 << x;
    }
    for (int S = 0; S < (1 << tot); ++S)
    {
        int cnt = 0, allS = 0;
        for (int i = 0; i < tot; ++i)
            if ((S >> i) & 1)
            {
                allS |= need[i];
                ++cnt;
            }
        f[S] = (S & allS) == 0 ? C(n1 + (m - tot) - 1, m - cnt - 1) : 0;
    }
    for (int i = 0; i < tot; ++i)
        for (int S = 0; S < (1 << tot); ++S)
            if ((S >> i) & 1)
                (f[S] += f[S ^ (1 << i)]) %= mod;

    ll ans = 0;
    for (int S = 0; S < (1 << tot); ++S)
    {
        int cnt = 0, allS = 0;
        for (int i = 0; i < tot; ++i)
            if ((S >> i) & 1)
            {
                allS |= need[i];
                ++cnt;
            }
        auto times = (S & allS) == 0 ? C(n2 + (m - tot) - 1, m - cnt - 1) : 0;
        (ans += f[((1 << tot) - 1) ^ S] *  times) %= mod;
    }
    cout << (ans + mod) % mod << '\n';

    for (int i = 0; i < tot; ++i)
        need[i] = 0;
    tot = 0;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    inv[1] = 1;
    for (int i = 2; i <= 20; ++i)
        inv[i] = (-mod / i) * inv[mod % i] % mod;
    int T = 1;
    cin >> T;
    while (T--)
        _main();
    return 0;
}