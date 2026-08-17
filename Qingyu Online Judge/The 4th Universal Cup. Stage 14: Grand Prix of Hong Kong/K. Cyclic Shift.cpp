#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
struct Main
{
    int n;
    vector<int> a, rk;
    vector<pair<int, int>> b;
    vector<vector<int>> g;
    Main()
    {
        cin >> n;
        a.resize(n), rk.resize(n);
        g.resize(n + 5);
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
            g[a[i]].push_back(i);
        }
        set<int> se;
        int m = *max_element(a.begin(), a.end());
        int w = 0;
        for (int i : g[m])
        {
            rk[i] = w;
            se.insert(i);
        }
        b.resize(n);
        for (int i = m - 1; i >= 1; --i)
        {
            if (g[i].empty())
                continue;
            for (int j : g[i])
            {
                auto it = se.upper_bound(j);
                int p = (it == se.end() ? *se.begin() + n : *it);
                b[j] = {p - j, rk[p % n]};
            }
            sort(g[i].begin(), g[i].end(), [&](int x, int y)
                 { return b[x] < b[y]; });
            pair<int, int> las(-1, -1);
            for (int j : g[i])
            {
                rk[j] = (w += (las != b[j]));
                las = b[j];
                se.insert(j);
            }
        }
        int h = (int)(max_element(rk.begin(), rk.end()) - rk.begin());
        for (int i = 0, j = 0; i < n; ++i)
            cout << (j = max(j, a[(i + h) % n])) << ' ';
        cout << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}

