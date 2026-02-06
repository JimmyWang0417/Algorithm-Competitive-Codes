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
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> p(m);
        vector<int> fa(n + 5);
        for (auto &[x, y] : p)
            cin >> x >> y;
        int maxx = 0;
        for (auto [x, y] : p)
            maxx = max(maxx, y - x);
        int cnt = 0;
        for (auto [x, y] : p)
            cnt += (y - x == maxx);
        if (cnt == 1)
        {
            int where = 0;
            for (auto [x, y] : p)
            {
                if (maxx == y - x)
                {
                    where = x;
                    break;
                }
            }
            for (auto [x, y] : p)
            {
                for (int i = x + 1; i <= y; ++i)
                    fa[i] = i - 1;
                if (y - x != maxx)
                    fa[x] = where;
            }
        }
        else
        {
            int where = (int)(min_element(p.begin(), p.end(), [](auto x, auto y)
                                          { return x.second - x.first < y.second - y.first; }) -
                              p.begin());
            int root = (int)(max_element(p.begin(), p.end(), [](auto x, auto y)
                                    { return x.second - x.first < y.second - y.first; }) -
                        p.begin());
            if (p[where].second - p[where].first > maxx - 2)
            {
                cout << "IMPOSSIBLE\n";
                return;
            }
            fa[p[where].first] = p[root].first + 1;
            for (auto [x, y] : p)
            {
                for (int i = x + 1; i <= y; ++i)
                    fa[i] = i - 1;
                if (x == p[root].first || fa[x])
                    continue;
                fa[x] = p[root].first;
            }
        }
        for (auto i = 1; i <= n; ++i)
            cout << fa[i] << ' ';
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