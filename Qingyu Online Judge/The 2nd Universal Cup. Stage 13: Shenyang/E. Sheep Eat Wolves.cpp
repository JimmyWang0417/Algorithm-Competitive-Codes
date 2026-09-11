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
constexpr int mod = 1e9 + 7;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
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
    int n;
    int x, y, p, q;
    auto calc(int i, int j, int c)
    {
        return i * (y + 1) * 2 + j * 2 + c;
    }
    vector<vector<int>> G;
    vector<int> dis;
    Main()
    {
        cin >> x >> y >> p >> q;
        n = (x + 1) * (y + 1) * 2;
        G.resize(n);
        dis.resize(n, -1);
        for (int i = 0; i <= x; ++i)
            for (int j = 0; j <= y; ++j)
                for (int l = 0; l <= i; ++l)
                    for (int r = 0; r <= j && l + r <= p; ++r)
                        if (i - l == 0 || (j - r) <= (i - l) + q)
                        {
                            int u = calc(i, j, 0);
                            int v = calc(x - (i - l), y - (j - r), 1);
                            G[v].emplace_back(u);
                            u = calc(i, j, 1);
                            v = calc(x - (i - l), y - (j - r), 0);
                            G[v].emplace_back(u);
                        }
        queue<int> que;
        for (int i = 0; i <= y; ++i)
        {
            que.push(calc(x, i, 1));
            dis[calc(x, i, 1)] = 0;
        }
        while (!que.empty())
        {
            int u = que.front();
            que.pop();
            for (auto v : G[u])
                if (dis[v] == -1)
                {
                    dis[v] = dis[u] + 1;
                    que.push(v);
                }
        }
        cout << dis[calc(x, y, 0)] << '\n';
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
