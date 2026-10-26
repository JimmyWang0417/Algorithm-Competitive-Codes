#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
struct Main
{
    int n, m, k;
    vector<int> a;
    vector<tuple<int, int, int>> p;
    Main()
    {
        cin >> n >> m >> k;
        a.resize(n + 5), p.resize(m);
        for (auto &[u, v, w] : p)
        {
            cin >> u >> v >> w;
            for (int i = 0; i < k; ++i)
                if ((w >> i) & 1)
                {
                    a[u] |= 1 << i;
                    a[v] |= 1 << i;
                }
        }
        for (auto [u, v, w] : p)
        {
            if ((a[u] & a[v]) != w)
            {
                cout << "-1\n";
                return;
            }
        }
        i64 res = 0;
        for (int i = 1; i <= n; ++i)
            res += a[i];
        cout << res << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
