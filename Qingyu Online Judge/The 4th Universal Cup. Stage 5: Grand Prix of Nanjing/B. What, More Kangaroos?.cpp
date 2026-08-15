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
struct Main
{
    int n, m;
    vector<tuple<int, int, int>> a;
    auto arg(const pair<int, int> &p)
    {
        auto [x, y] = p;
        if (-y < 0)
            x = -x, y = -y;
        return make_pair(-y, x);
    }
    auto cross(const pair<int, int> &p, const pair<int, int> &q)
    {
        return (i64)p.first * q.second - (i64)p.second * q.first;
    }
    auto solve(int xx, int yy)
    {
        vector<pair<int, int>> b, c, d;
        for (auto [x, y, _c] : a)
        {
            int p = x * xx, q = y * yy;
            if (p >= 0 && q >= 0)
                continue;
            if (p <= 0 && q <= 0)
                b.emplace_back(p, q);
            else if (p < 0)
                c.emplace_back(p, q);
            else
                d.emplace_back(p, q);
        }
        sort(c.begin(), c.end(), [&](auto x, auto y)
             { return cross(arg(x), arg(y)) > 0; });
        sort(d.begin(), d.end(), [&](auto x, auto y)
             { return cross(arg(x), arg(y)) > 0; });
        int res = (int)max(c.size(), d.size());
        for (int i = 0, j = 0; i < (int)c.size(); ++i)
        {
            while (j < (int)d.size() && cross(arg(d[j]), arg(c[i])) > 0)
                ++j;
            res = max(res, j + (int)c.size() - i);
        }
        return res + (int)b.size();
    }
    Main()
    {
        cin >> n;
        a.resize(n);
        for (auto &[x, y, c] : a)
            cin >> x >> y >> c;
        cout << max({solve(1, 1), solve(1, -1), solve(-1, 1), solve(-1, -1)}) << '\n';
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
