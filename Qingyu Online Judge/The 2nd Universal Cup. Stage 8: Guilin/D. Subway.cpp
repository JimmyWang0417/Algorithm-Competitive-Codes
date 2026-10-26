#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
struct Main
{
    int n;
    vector<tuple<int, int, int>> a;
    Main()
    {
        cin >> n;
        a.resize(n);
        int m = 0;
        for (auto &[x, y, c] : a)
        {
            cin >> x >> y >> c;
            m = max(m, c);
        }
        ranges::sort(a);
        cout << m << '\n';
        for (int k = 1; k <= m; ++k)
        {
            vector<pair<int, int>> p;
            for (auto [x, y, c] : a)
            {
                if (k <= c)
                    p.emplace_back(x, y);
                p.emplace_back(x - 2 * k - 1, y + 1000001 * k + 500001);
            }
            cout << p.size();
            for (auto [x, y] : p)
                cout << ' ' << x << ' ' << y;
            cout << '\n';
        }
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
