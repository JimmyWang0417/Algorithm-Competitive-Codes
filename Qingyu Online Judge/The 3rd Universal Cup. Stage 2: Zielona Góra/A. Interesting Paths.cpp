#include <bits/stdc++.h>
using namespace std;
int used[1001001];
vector<int> g[1001001];
int n, m;
int ans, f[1001001];
bool dfs(int x)
{
    if (used[x] == 1)
        return f[x];

    used[x] = 1;
    ans--;

    for (auto y : g[x])
    {
        if (used[y] == 1)
            ans += f[y], f[x] |= f[y];
        else
            f[x] |= dfs(y), ans++;
    }

    return f[x];
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    used[n] = 1;
    f[n] = 1;

    for (int i = 1, x, y; i <= m; i++)
        cin >> x >> y, g[x].push_back(y);

    ans = 1;
    dfs(1);
    cout << ans << "\n";
}