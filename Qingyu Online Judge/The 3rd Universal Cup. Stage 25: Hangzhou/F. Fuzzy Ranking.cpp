#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
constexpr int N = 2e5 + 5;
int n, m, q;
vector<int> G[N];
int dfn[N], low[N], dfstime;
int belong[N], color;
int st[N], top;
inline void tarjan(int u)
{
    st[++top] = u;
    dfn[u] = low[u] = ++dfstime;
    for (int v : G[u])
    {
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (!belong[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u])
    {
        belong[u] = ++color;
        while (st[top] != u)
            belong[st[top--]] = color;
        --top;
    }
}
vector<int> a[N], b[N];
vector<ll> c[N];
vector<int> cnt[N];
inline void clear()
{
    for (int i = 1; i <= n; ++i)
    {
        G[i].clear();
        dfn[i] = low[i] = belong[i] = 0;
    }
    for (int i = 1; i <= m; ++i)
    {
        a[i].clear();
        b[i].clear();
        c[i].clear();
        cnt[i].clear();
    }
    dfstime = color = 0;
}
inline void _main()
{
    cin >> n >> m >> q;
    for (int j = 1; j <= m; ++j)
    {
        a[j].resize(n + 5);
        b[j].resize(n + 5);
        c[j].resize(n + 5);
        cnt[j].resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[j][i];
        for (int i = 1; i < n; ++i)
            G[a[j][i]].push_back(a[j][i + 1]);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int j = 1; j <= m; ++j)
    {
        for (int i = 1; i <= n; ++i)
        {
            c[j][i] = c[j][i - 1] + cnt[j][belong[a[j][i]]];
            b[j][i] = ++cnt[j][belong[a[j][i]]];
        }
    }
    ll ans = 0;
    while (q--)
    {
        int id, l, r;
        cin >> id >> l >> r;
        id = (int)((id + ans) % m + 1);
        l = (int)((l + ans) % n + 1);
        r = (int)((r + ans) % n + 1);
        cout << (ans = c[id][r] - c[id][l - 1] -
                    (ll)b[id][l - 1] * min(cnt[id][belong[a[id][l - 1]]] - b[id][l - 1], r - l + 1)) << '\n';
    }
    clear();
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        _main();
    return 0;
}