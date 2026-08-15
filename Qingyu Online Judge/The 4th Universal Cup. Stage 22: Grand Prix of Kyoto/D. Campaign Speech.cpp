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
constexpr int mod = 998244353;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
    a %= mod;
    i64 res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
struct Main
{
    int n, m;
    vector<pair<int, int>> a;
    map<int, set<tuple<int, int, int>>> row, col;
    Main()
    {
        cin >> n >> m;
        a.resize(n);
        for (auto &[x, y] : a)
            cin >> x >> y;
        for (int i = 0; i < n; ++i)
        {
            if (a[i].first == a[(i + 1) % n].first)
            {
                int l = a[i].second, r = a[(i + 1) % n].second;
                if (l > r)
                    swap(l, r);
                row[a[i].first].emplace(l, r, i);
            }
            else
            {
                int l = a[i].first, r = a[(i + 1) % n].first;
                if (l > r)
                    swap(l, r);
                col[a[i].second].emplace(l, r, i);
            }
        }
        vector<vector<int>> G(n);
        for (int i = 0; i < m; ++i)
        {
            int x, y;
            cin >> x >> y;
            if (row.find(x) != row.end())
            {
                auto it = row[x].upper_bound({y, INT_MAX, INT_MAX});
                if (it != row[x].begin() && get<1>(*prev(it)) >= y)
                {
                    G[get<2>(*prev(it))].emplace_back(y);
                    continue;
                }
            }
            if (col.find(y) != col.end())
            {
                auto it = col[y].upper_bound({x, INT_MAX, INT_MAX});
                if (it != col[y].begin() && get<1>(*prev(it)) >= x)
                {
                    G[get<2>(*prev(it))].emplace_back(x);
                    continue;
                }
            }
            assert(false);
        }
        i64 all = 0, res = LLONG_MIN;
        for (int i = 0; i < n; ++i)
        {
            if (a[i].first == a[(i + 1) % n].first)
            {
                int l = a[i].second, r = a[(i + 1) % n].second;
                if (l <= r)
                    ranges::sort(G[i]);
                else
                    ranges::sort(G[i], greater<>());
                G[i].insert(G[i].begin(), l);
                G[i].push_back(r);
                all += abs(l - r);
            }
            else
            {
                int l = a[i].first, r = a[(i + 1) % n].first;
                if (l <= r)
                    ranges::sort(G[i]);
                else
                    ranges::sort(G[i], greater<>());
                G[i].insert(G[i].begin(), l);
                G[i].push_back(r);
                all += abs(l - r);
            }
        }
        {
            i64 pre = LLONG_MIN;
            for (int i = 0; i < n; ++i)
            {
                for (int j = 1; j + 1 < (int)G[i].size(); ++j)
                {
                    res = max(res, pre += abs(G[i][j] - G[i][j - 1]));
                    pre = 0;
                }
                pre += abs(G[i][(int)G[i].size() - 2] - G[i][(int)G[i].size() - 1]);
                // cout << ' ' << pre << ' ' << res << '\n';
            }
            for (int i = 0; i < n; ++i)
            {
                for (int j = 1; j + 1 < (int)G[i].size(); ++j)
                {
                    res = max(res, pre += abs(G[i][j] - G[i][j - 1]));
                    pre = 0;
                }
                pre += abs(G[i][(int)G[i].size() - 2] - G[i][(int)G[i].size() - 1]);
            }
        }
        cout << all - res << '\n';
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
