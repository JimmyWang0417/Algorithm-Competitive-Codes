#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int N = 200010;
struct ringCount
{
    auto three(int n, const vector<pair<int, int>> &edges)
    {
        vector<int> deg(n + 5);
        for (auto [u, v] : edges)
        {
            ++deg[u];
            ++deg[v];
        }
        vector<vector<int>> g(n + 5);
        for (auto [u, v] : edges)
        {
            if (deg[u] < deg[v] || (deg[u] == deg[v] && u > v))
                swap(u, v);
            g[u].push_back(v);
        }
        vector<bool> exist(n + 5);
        int ans = 0;
        for (int u = 1; u <= n; ++u)
        {
            for (int v : g[u])
                exist[v] = true;
            for (int v : g[u])
                for (int w : g[v])
                    ans += exist[w];
            for (int v : g[u])
                exist[v] = false;
        }
        return ans;
    }
};
struct Main
{
    Main()
    {
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> edges(m);
        for (auto &[u, v] : edges)
            cin >> u >> v;
        cout << ringCount().three(n, edges) << '\n';
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