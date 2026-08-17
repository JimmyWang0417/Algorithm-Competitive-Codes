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
    Main()
    {
        int n;
        cin >> n;
        vector<vector<int>> a(n + 5, vector<int>(n + 5));
        for (int i = 1; i <= n; ++i)
        {
            for (int j = i; j <= n; ++j)
            {
                cin >> a[i][j];
                a[j][i] = a[i][j];
            }
        }
        vector<int> fa(n + 5);
        vector<int> in(n + 5);
        vector g(n + 5, vector<int>());
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
            {
                if (i == j)
                    continue;
                if ((a[1][i] ^ a[1][j] ^ a[i][j]) == i)
                    g[i].push_back(j);
            }
        for (int u = 1; u <= n; ++u)
            for (int v : g[u])
                ++in[v];
        queue<int> q;
        for (int u = 1; u <= n; ++u)
            if (!in[u])
                q.push(u);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v : g[u])
            {
                fa[v] = u;
                if (!--in[v])
                    q.push(v);
            }
        }
        for (int i = 2; i <= n; ++i)
            cout << fa[i] << ' ' << i << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
