#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    char x;
    map<string, vector<pair<int, int>>> use;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            string o;
            for (int p = 1; p <= k; p++)
            {
                cin >> x;
                o += x;
            }
            if (use[o].size() <= 1)
                use[o].push_back({i, j});
        }
    }
    for (auto &[a, b] : use)
    {
        if (b.size() == 1)
        {
            cout << b[0].first << " " << b[0].second << "\n";
            return 0;
        }
    }
}