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
    vector<vector<int>> g;
    vector<int> dfn, low;
    int dfstime;
    vector<int> answer;
    auto tarjan(int u, int _fa) -> void
    {
        dfn[u] = low[u] = ++dfstime;
        int cnt0 = 0, cnt1 = 0, son = 0;
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            if (!dfn[v])
            {
                ++son;
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (dfn[u] == low[v])
                    ++cnt1;
                else if (dfn[u] < low[v])
                    ++cnt0;
            }
            else
                low[u] = min(low[u], dfn[v]);
        }
        if ((_fa && (cnt0 || cnt1)) || (!_fa && son >= 2))
        {
            if (_fa)
            {
                if (!cnt0 && low[u] < dfn[u])
                    answer.push_back(u);
            }
            else if (!cnt0 && cnt1 >= 2)
                answer.push_back(u);
        }
    }
    Main() : dfstime(0)
    {
        cin >> n >> m;
        g.resize(n + 5);
        dfn.resize(n + 5), low.resize(n + 5);
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        tarjan(1, 0);
        if (answer.empty())
            cout << "Empty\n";
        else
        {
            sort(answer.begin(), answer.end());
            for (int i : answer)
                cout << i << ' ';
            cout << '\n';
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
