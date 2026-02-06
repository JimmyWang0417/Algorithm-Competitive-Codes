#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
mt19937 rnd((random_device())());
struct Main
{
    Main()
    {
        int n, f;
        cin >> n >> f;
        vector<int> p(n);
        vector<pair<int, int>> a(n);
        iota(p.begin(), p.end(), 0);
        i64 res = 0;
        for (auto &[x, y] : a)
        {
            cin >> x >> y;
            res += y - x;
        }
        sort(p.begin(), p.end(), [&](int x, int y)
             { return a[x].first < a[y].first; });
        vector<int> q;
        vector<bool> vis(n);
        q.reserve(n);
        for (int i = 0; i < n; ++i)
            if (f <= a[p[i]].second)
            {
                res += max(0, a[p[i]].first - f);
                vis[i] = true;
                q.push_back(p[i]);
                f = a[p[i]].second;
            }
        for (int i = n - 1; i >= 0; --i)
        {
            if (vis[i])
                continue;
            q.push_back(p[i]);
        }
        cout << res << '\n';
        for (auto i : q)
            cout << i + 1 << ' ';
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