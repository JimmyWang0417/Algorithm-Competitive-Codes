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
struct Main
{
    int n;
    vector<int> sze;
    vector<i64> sum;
    vector<vector<i64>> dp;
    vector<vector<pair<int, int>>> G;
    vector<i64> answer;
    auto dfs(int u, int _fa) -> void
    {
        sze[u] = 1;
        vector<i64> f = {0}, g = {0}, h = {0};
        for (auto [v, w] : G[u])
        {
            if (v == _fa)
                continue;
            dfs(v, u);
            sum[u] += (sum[v] += w);
            vector<i64> nf = f, ng = g, nh = h;
            nf.insert(nf.end(), 2 * sze[v], LONG_LONG_MIN / 2);
            ng.insert(ng.end(), 2 * sze[v], LONG_LONG_MIN / 2);
            nh.insert(nh.end(), 2 * sze[v], LONG_LONG_MIN / 2);
            for (int i = 0; i < (int)f.size(); ++i)
            {
                nf[i + sze[v] * 2] = max(nf[i + sze[v] * 2], f[i] + sum[v] * 2);
                ng[i + sze[v] * 2] = max(ng[i + sze[v] * 2], g[i] + sum[v] * 2);
                nh[i + sze[v] * 2] = max(nh[i + sze[v] * 2], h[i] + sum[v] * 2);
                for (int j = 0; j < (int)dp[v].size(); ++j)
                {
                    ng[i + j + 1] = max(ng[i + j + 1], f[i] + dp[v][j] + w);
                    nh[i + j + 1] = max(nh[i + j + 1], g[i] + dp[v][j] + w);
                }
            }
            swap(nf, f), swap(ng, g), swap(nh, h);
            sze[u] += sze[v];
        }
        for (int i = 0; i < (int)h.size(); ++i)
            answer[i] = max(answer[i], h[i]);
        swap(dp[u], g);
    }
    Main()
    {
        cin >> n;
        sze.resize(n + 5);
        G.resize(n + 5);
        for (int i = 1; i < n; ++i)
        {
            int u, v, c;
            cin >> u >> v >> c;
            G[u].emplace_back(v, c);
            G[v].emplace_back(u, c);
        }
        sze.resize(n + 5), sum.resize(n + 5);
        dp.resize(n + 5);
        answer.assign(n * 2 - 1, LONG_LONG_MIN / 2);
        dfs(1, 0);
        for (int i = 0; i <= 2 * n - 2; ++i)
            cout << sum[1] * 2 - answer[i] << ' ';
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

