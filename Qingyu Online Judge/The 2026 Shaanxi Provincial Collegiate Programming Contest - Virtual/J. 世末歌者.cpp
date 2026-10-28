#include <bits/stdc++.h>
using namespace std;
struct Main
{
    int n;
    auto query(int x)
    {
        cout << "? " << x << endl;
        int y;
        cin >> y;
        return y;
    }
    vector<int> a;
    vector<bool> vis;
    Main()
    {
        cin >> n;
        a.resize(n + 5);
        vis.resize(n + 5);
        for (int i = 1; i < n; ++i)
            while (query(i));
        for (int i = 1; i <= n; ++i)
            a[i] = query(i);
        int cnt = 0;
        while (cnt < n - 1)
        {
            for (int i = 2; i <= n; ++i)
            {
                if (vis[i])
                    continue;
                if (query(i) != a[i])
                {
                    if (a[i])
                        query(i);
                    ++cnt;
                    vis[i] = true;
                }
            }
        }
        for (int i = 1; i <= n; ++i)
        {
            if (a[i] && i != 1)
                continue;
            query(i), query(i);
        }
        cout << "!" << endl;
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
