#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve()
{
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> tip(n);
    for (int i = 0; i < n; i++)
    {
        cin >> tip[i];
    }

    unordered_map<int, int> ans;
    auto cul = [&](auto &&self, int x) -> int
    {
        if (x == 1)
        {
            return 1;
        }
        if (x <= 0)
        {
            return 0;
        }
        if (ans[x])
        {
            return ans[x];
        }
        int ma = 0;
        for (int i = 0; i < n; i++)
        {
            if (tip[i] <= x)
            {
                ma = tip[i];
            }
        }
        int len = (x + 1) / (2 * ma);
        int o = self(self, ma - 1);
        if ((x + 1) % (2 * ma) <= ma)
        {
            return ans[x] = len * (o + ma) + self(self, (x + 1) % (2 * ma) - 1);
        }
        else
        {
            return ans[x] = len * (o + ma) + o + (x + 1) % (2 * ma) - ma;
        }
    };

    cout << cul(cul, r) - cul(cul, l - 1) << "\n";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while (t--)
    {
        solve();
    }
}
// 1 2 4 3
// 3 4 2 1