#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 405;
int n, m;
int f[N][N], g[N][N], h[N][N];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (i != j)
                f[i][j] = g[i][j] = h[i][j] = 1e18;
    for (int i = 1; i <= m; ++i)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        f[a][b] = min(f[a][b], c);
        if (d >= 1)
            g[a][b] = min(g[a][b], c);
        if (d >= 2)
            h[a][b] = min(h[a][b], c);
    }
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                h[i][j] = min(h[i][j], g[i][j] * 2 + f[j][i]);
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                h[i][j] = min(h[i][j], h[i][k] + h[k][j]);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            cout << (h[i][j] > 1e18 / 2 ? -1 : h[i][j]) << ' ';
        cout << '\n';
    }
    return 0;
}