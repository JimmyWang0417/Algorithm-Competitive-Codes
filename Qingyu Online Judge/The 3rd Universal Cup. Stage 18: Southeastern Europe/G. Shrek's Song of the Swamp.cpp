#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e6 + 5;
int n, m, a[N];
int p[N], tot;
int f[N][2], g[N];
inline void _main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        p[i] = a[i];
    }
    sort(p + 1, p + 1 + n);
    m = (int)(unique(p + 1, p + 1 + n) - p - 1);
    for (int i = 1; i <= n; ++i)
        a[i] = (int)(lower_bound(p + 1, p + 1 + m, a[i]) - p);
    for (int i = 1; i <= m; ++i)
        g[i] = ~0x3f3f3f3f;
    f[0][1] = 0, f[0][0] = ~0x3f3f3f3f;
    int ans = 0;
    for (int i = 1, j = 0; i <= n; ++i)
    {
        f[i][0] = j + 1;
        f[i][1] = g[a[i]] + 1;
        j = max(j, f[i][1]);
        g[a[i]] = max(g[a[i]], max(f[i][0], f[i][1]));
        ans = max(ans, f[i][1]);
    }
    cout << ans << '\n';
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