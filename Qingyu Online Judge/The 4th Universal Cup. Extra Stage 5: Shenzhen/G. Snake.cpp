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
    int n, m, sr, sc;
    Main()
    {
        cin >> n >> m >> sr >> sc;
        vector<pair<int, int>> p;
        if (m % 2 == 0)
        {
            for (int i = 1; i <= n; ++i)
                p.emplace_back(i, 1);
            for (int i = 2; i <= m; ++i)
                p.emplace_back(n, i);
            for (int i = n - 1; i >= 1; --i)
                p.emplace_back(i, m);
            for (int i = m - 1; i >= 2; --i)
            {
                if (i & 1)
                    for (int j = 1; j < n; ++j)
                        p.emplace_back(j, i);
                else
                    for (int j = n - 1; j >= 1; --j)
                        p.emplace_back(j, i);
            }
        }
        else if (n % 2 == 0)
        {
            for (int i = 1; i <= m; ++i)
                p.emplace_back(1, i);
            for (int i = 2; i <= n; ++i)
                p.emplace_back(i, m);
            for (int i = m - 1; i >= 1; --i)
                p.emplace_back(n, i);
            for (int i = n - 1; i >= 2; --i)
            {
                if (i & 1)
                    for (int j = 1; j < m; ++j)
                        p.emplace_back(i, j);
                else
                    for (int j = m - 1; j >= 1; --j)
                        p.emplace_back(i, j);
            }
        }
        // for (auto [x, y] : p)
        //     cerr << x << ' ' << y << endl;
        auto next = [](auto x, auto y)
        {
            if (x.first - 1 == y.first)
                return 'U';
            else if (x.first + 1 == y.first)
                return 'D';
            else if (x.second + 1 == y.second)
                return 'R';
            else
                return 'L';
        };
        int len = 1;
        int r, c;
        cin >> r >> c;
        auto las = make_pair(sr, sc);
        auto print = [&](auto y)
        {
            if ((n & 1) && (m & 1) && y == make_pair(2, 2) && r == 1 && c == 1)
                y = make_pair(1, 1);
            cout << next(las, y);
            if (y == make_pair(r, c))
            {
                cout << endl;
                if (++len < n * m)
                    cin >> r >> c;
            }
            las = y;
        };
        if (!p.empty())
        {
            for (int i = 0; i < (int)p.size(); ++i)
            {
                if (p[i] == make_pair(sr, sc))
                {
                    for (int j = i + 1; j < (int)p.size() && len < n * m; ++j)
                        print(p[j]);
                    break;
                }
            }
            while (len < n * m)
            {
                for (int i = 0; i < (int)p.size() && len < n * m; ++i)
                    print(p[i]);
            }
            return;
        }
        else
        { // 先不要(1, 1)
            for (int i = 2; i < n; ++i)
            {
                if (i & 1)
                {
                    p.emplace_back(i, 1);
                    p.emplace_back(i, 2);
                }
                else
                {
                    p.emplace_back(i, 2);
                    p.emplace_back(i, 1);
                }
            }
            for (int i = 1; i <= m; ++i)
                p.emplace_back(n, i);
            for (int i = n - 1; i >= 1; --i)
                p.emplace_back(i, m);
            for (int i = m - 1; i >= 3; --i)
            {
                if (i & 1)
                    for (int j = n - 1; j >= 1; --j)
                        p.emplace_back(j, i);
                else
                    for (int j = 1; j < n; ++j)
                        p.emplace_back(j, i);
            }
            p.emplace_back(1, 2);

            // for (auto [x, y] : p)
            //     cerr << x << ' ' << y << endl;
            if (sr == 1 && sc == 1)
                sr = sc = 2;
            for (int i = 0; i < (int)p.size(); ++i)
            {
                if (p[i] == make_pair(sr, sc))
                {
                    for (int j = i + 1; j < (int)p.size() && len < n * m; ++j)
                        print(p[j]);
                    break;
                }
            }
            while (len < n * m)
            {
                for (int i = 0; i < (int)p.size() && len < n * m; ++i)
                    print(p[i]);
            }
        }
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

