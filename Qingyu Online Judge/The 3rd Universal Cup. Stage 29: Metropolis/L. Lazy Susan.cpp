#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5005;
int n, m, a[N];
int f[N][N], g[N][N];
vector<pair<int, int>> L[N], R[N];
int headL[N], headR[N];
int minL[N], minR[N];
inline void _main()
{
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            f[i][j] = g[i][j] = INT_MIN / 2;
    for (int i = 0; i < n; ++i)
    {
        f[i][(i + n - 1) % n] = g[i][(i + n - 1) % n] = INT_MAX / 2;
        minL[i] = minR[i] = INT_MAX / 2;
    }
    for (int i = 0; i < m; ++i)
    {
        int p, d, t;
        cin >> p >> d >> t;
        int l = (p - a[p] + n) % n, r = (p + a[p] + n) % n;
        l = (l + n - d) % n, r = (r + n - d) % n;
        if (a[p] * 2 + 1 >= n)
            r = (l + n - 1) % n;
        int len = (r - l + n) % n;
        L[l].emplace_back(len, t);
        R[r].emplace_back(len, t);
    }
    for (int i = 0; i < n; ++i)
    {
        sort(L[i].begin(), L[i].end());
        sort(R[i].begin(), R[i].end());
    }
    for (int len = n - 1; len >= 1; --len)
    {
        for (int i = 0; i < n; ++i)
        {
            while (headL[i] < (int)L[i].size() && L[i][headL[i]].first < n - len)
                minL[i] = min(minL[i], L[i][headL[i]++].second);
            while (headR[i] < (int)R[i].size() && R[i][headR[i]].first < n - len)
                minR[i] = min(minR[i], R[i][headR[i]++].second);
        }
        for (int i = 0, j, k; i < n; ++i)
        {
            j = (i + len) % n, k = (i + 1) % n;
            f[k][j] = max(f[k][j], min(f[i][j], minR[i]) - 1);
            g[k][j] = max(g[k][j], min(f[i][j], minR[i]) - len);

            k = (j + n - 1) % n;
            f[i][k] = max(f[i][k], min(g[i][j], minL[j]) - len);
            g[i][k] = max(g[i][k], min(g[i][j], minL[j]) - 1);
        }
    }
    for (int i = 0; i < n; ++i)
        cout << (f[i][i] >= 0);
    cout << '\n';
    for (int i = 0; i < n; ++i)
    {
        L[i].clear(), R[i].clear();
        headL[i] = headR[i] = 0;
    }
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