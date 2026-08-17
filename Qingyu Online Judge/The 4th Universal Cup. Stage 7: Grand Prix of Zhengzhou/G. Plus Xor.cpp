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
    i64 a, b, c, d;
    Main()
    {
        cin >> a >> b >> c;
        d = 1;
        while (d <= b)
            d <<= 1;
        vector<bool> vis(d * b + b + 5);
        queue<i64> q;
        q.push(b);
        vis[b] = true;
        while (!q.empty())
        {
            auto u = q.front() - b + a;
            q.pop();
            if (u <= c && u % b == c % b)
            {
                cout << "YES\n";
                return;
            }
            {
                auto v = (u ^ b) - a + b;
                if (0 <= v && v < (int)vis.size())
                {
                    if (!vis[v])
                    {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
            {
                auto v = (u + b) - a + b;
                if (0 <= v && v < (int)vis.size())
                {
                    if (!vis[v])
                    {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
        }
        cout << "NO\n";
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int test = 1;
    cin >> test;
    while (test--)
        Main();
    return 0;
}

