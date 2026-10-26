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
    int n;
    vector<bool> p;
    vector<vector<int>> g;
    vector<set<pair<i64, int>>> se;
    vector<int> a, b;
    vector<int> answer;
    auto dfs(int u, int _fa, bool col) -> void
    {
        if (p[u] == col)
            a[u] = a[_fa] + 1, b[u] = b[_fa] - 1;
        else
            a[u] = a[_fa] - 1, b[u] = b[_fa] + 3;
        se[u].emplace(a[u], b[u]);
        auto merge = [&](set<auto> &x, set<auto> &y)
        {
            if (x.size() < y.size())
                swap(x, y);
            for (auto [A, B] : y)
            {
                auto it = x.lower_bound(make_pair(a[u] + a[_fa] - A, INT_MIN));
                if (it != x.end())
                    answer[u] = max(answer[u], it->second + B - b[u] - b[_fa]);
            }
            for (auto [A, B] : y)
            {
                auto it = x.lower_bound(make_pair(A, INT_MIN));
                if (it != x.end() && B <= it->second)
                    continue;
                if (it != x.end() && it->first == A)
                    it = x.erase(it);
                while (it != x.begin() && prev(it)->second <= B)
                    it = x.erase(prev(it));
                x.emplace(A, B);
            }
            y.clear();
        };
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            dfs(v, u, col);
            merge(se[u], se[v]);
        }
    }
    Main()
    {
        cin >> n;
        {
            string s;
            cin >> s;
            p.resize(n + 5);
            for (int i = 1; i <= n; ++i)
                p[i] = s[i - 1] - '0';
        }
        se.resize(n + 5);
        g.resize(n + 5);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            cin >> u >> v;
            g[u].emplace_back(v);
            g[v].emplace_back(u);
        }
        answer.assign(n + 5, -1);
        a.resize(n + 5), b.resize(n + 5);
        dfs(1, 0, 0);
        se[1].clear();
        dfs(1, 0, 1);
        for (int i = 1; i <= n; ++i)
            cout << answer[i] << '\n';
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
