#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 5e5 + 5;
constexpr int mod = 998244353;
constexpr char match[] = "docker";
int n, m;
ll f[N];
int g[N];
int cost[N];
char str[N];
int diff[N];
inline void clear()
{
    for (int i = 0; i <= n / 6; ++i)
        diff[i] = 0;
}
inline auto calc(int mid)
{
    for (int i = 1; i <= n; ++i)
    {
        if (i >= 6 && cost[i] == 0)
            f[i] = f[i - 6] + 1, g[i] = g[i - 6];
        else
            f[i] = f[i - 1], g[i] = g[i - 1];
        if (i >= 6 && f[i - 6] + cost[i] - mid < f[i])
            f[i] = f[i - 6] + cost[i] - mid, g[i] = g[i - 6] + 1;
    }
    return make_pair(f[n], g[n]);
}
inline int ask(int cnt)
{
    if (cnt == -1)
        return 1e9;
    int l = -1e9, r = 1e9;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (calc(mid).second <= cnt)
            l = mid + 1;
        else
            r = mid - 1;
    }
    auto [F, G] = calc(r);
    return (int)(F + cnt * r);
}
inline void _main()
{
    cin >> (str + 1);
    n = (int)strlen(str + 1);
    for (int i = 6; i <= n; ++i)
    {
        cost[i] = 0;
        for (int j = 0; j < 6; ++j)
            cost[i] += (str[i - 5 + j] != match[j]);
    }
    for (int i = 1; i <= n; ++i)
    {
        g[i] = g[i - 1];
        if (i >= 6 && cost[i] == 0)
            g[i] = max(g[i], g[i - 6] + 1);
    }
    cin >> m;
    int q = n / 6;
    for (int i = 1; i <= m; ++i)
    {
        int l, r;
        cin >> l >> r;
        if (l <= q)
            ++diff[l];
        if (r + 1 <= q)
            --diff[r + 1];
    }
    for (int i = 1; i <= q; ++i)
        diff[i] += diff[i - 1];
    int L = -1, R = -1, maxx = *max_element(diff, diff + q + 1);
    if (diff[g[n]] == maxx)
    {
        cout << "0" << '\n';
        return;
    }
    for (int i = g[n] - 1; i >= 0; --i)
        if (diff[i] == maxx)
        {
            L = i;
            break;
        }
    for (int i = g[n] + 1; i <= n; ++i)
        if (diff[i] == maxx)
        {
            R = i;
            break;
        }
    cout << min(ask(L), ask(R)) << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
    {
        _main();
        clear();
    }
    return 0;
}