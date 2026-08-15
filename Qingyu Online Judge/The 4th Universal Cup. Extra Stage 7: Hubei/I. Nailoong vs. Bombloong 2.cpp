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
    vector<vector<int>> G;
    vector<int> p;
    Main()
    {
        cin >> n;
        G.resize(n + 5);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        int r = 0;
        for (int i = 1; i <= n; ++i)
            if (G[i].size() == 1)
            {
                r = i;
                break;
            }
        queue<int> q;
        vector<bool> vis(n + 5);
        q.push(r);
        vis[r] = true;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            p.push_back(u);
            for (int v : G[u])
            {
                if (vis[v])
                    continue;
                vis[v] = true;
                q.push(v);
            }
        }
        p.erase(p.begin());
        p.erase(p.end() - 2, p.end());
        cout << p.size() << '\n';
        for (int i : p)
            cout << i << ' ';
        cout << '\n';
    }
};
struct Solve
{
    int n, m;
    Solve()
    {
        cin >> n >> m;
        assert(n - 3 == m);
        int j = 2;
        for (int i = 1, las = 0; i <= m; ++i)
        {
            int x;
            cin >> x;
            int cur = x - las;
            if (i == 1)
                --cur;
            else
                ++cur;
            while (cur--)
                cout << i << ' ' << j++ << '\n';
            las = x;
        }
        if (j < n)
        {
            cout << j - 1 << ' ' << j << '\n';
            j++;
        }
        cout << j++ << ' ' << 1 << '\n';
        assert(j == n + 1);
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    if (T == 1)
        Main();
    else
        Solve();

    // while (T--)
    //     Main();
    return 0;
}

