#include <bits/stdc++.h>
using namespace std;

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(k + 1);
    unordered_map<int, int> no;
    for (int i = 1; i <= k; i++)
    {
        cin >> a[i];
        no[a[i]] = 1;
    }
    vector<vector<int>> edge(n + 1);
    for (int i = 1, p, q; i <= m; i++)
    {
        cin >> p >> q;
        if (!no[p])
            edge[p].push_back(q);
        if (!no[q])
            edge[q].push_back(p);
    }

    vector<int> vis(n + 1);
    vector<pair<int, vector<int>>> ans;

    auto bfs = [&](int u) -> void
    {
        queue<int> use;
        use.push(u);
        vis[u] = 1;
        while (!use.empty())
        {
            int now = use.front();
            use.pop();
            pair<int, vector<int>> res;
            res.first = now;
            for (auto &v : edge[now])
            {
                if (vis[v])
                {
                    continue;
                }
                vis[v] = 1;
                use.push(v);
                res.second.push_back(v);
            }
            if (!res.second.empty())
                ans.push_back(res);
        }
    };

    for (int i = 1; i <= n; i++)
    {
        if (!no[i])
        {
            bfs(i);
            break;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            cout << "No" << "\n";
            return 0;
        }
    }
    cout << "Yes" << "\n";
    cout << ans.size() << "\n";
    for (auto &[a, b] : ans)
    {
        cout << a << " " << b.size() << " ";
        for (auto &i : b)
        {
            cout << i << " ";
        }
        cout << "\n";
    }
}