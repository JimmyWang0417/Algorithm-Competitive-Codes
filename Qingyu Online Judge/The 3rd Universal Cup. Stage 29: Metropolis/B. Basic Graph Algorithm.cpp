#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
int n, m;
set<int> g[N];
bool vis[N];
int p[N], tot;
vector<pair<int, int>> answer;
inline void dfs(int u)
{
    vis[u] = true;
    while (!g[u].empty() && tot <= n)
    {
        while (g[u].find(p[tot]) != g[u].end())
            dfs(p[tot++]);
        while (!g[u].empty() && vis[*g[u].begin()])
            g[u].erase(g[u].begin());
        if (!g[u].empty())
        {
            g[u].insert(p[tot]);
            answer.emplace_back(u, p[tot]);
        }
    }
}
inline void _main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        cin >> u >> v;
        g[u].insert(v);
        g[v].insert(u);
    }
    for (int i = 1; i <= n; ++i)
        g[0].insert(i);
    for (int i = 1; i <= n; ++i)
        cin >> p[i];
    tot = 1;
    dfs(0);
    cout << answer.size() << '\n';
    for (auto [x, y] : answer)
        cout << x << ' ' << y << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int test = 1;
    //	cin >> test;
    while (test--)
        _main();
    return 0;
}