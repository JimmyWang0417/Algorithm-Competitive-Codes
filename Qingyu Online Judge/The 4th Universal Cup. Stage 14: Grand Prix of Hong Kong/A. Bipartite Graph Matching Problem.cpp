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
    int n1, n2, m;
    vector<int> p, q;
    vector<int> belong;
    vector<vector<int>> G;
    auto dfs(int u) -> bool
    {
        for (int v : G[u])
        {
            if (p[v])
                continue;
            p[v] = u;
            if (!belong[v] || dfs(belong[v]))
            {
                q[belong[v] = u] = v;
                return true;
            }
        }
        return false;
    }
    Main()
    {
        cin >> n1 >> n2 >> m;
        p.resize(n1 + 5);
        q.resize(n2 + 5);
        belong.resize(n1 + 5);
        G.resize(n2 + 5);
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            cin >> u >> v;
            G[v].push_back(u);
        }
        i64 res = 0;
        for (int r = 1; r <= n2; ++r)
        {
            fill(p.begin(), p.end(), 0);
            if (!dfs(r))
            {
                int S = 0;
                for (int i = 1; i < r; ++i)
                    if (q[i] && p[q[i]])
                    {
                        S = i;
                        break;
                    }
                if (S)
                {
                    int u = S, v = 0;
                    while (u != r)
                    {
                        swap(q[u], v);
                        u = belong[v] = p[v];
                    }
                    swap(q[u], v);
                }
            }
            for (int i = r, j = 0; i >= 1; --i)
                (res += (i64)(j += !!q[i]) * i * r * ((i ^ r) + 1)) %= mod;
        }
        cout << res << '\n';
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

