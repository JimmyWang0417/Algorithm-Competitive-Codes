#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> f(n + 1);
    vector<pair<int, int>> e(m + 1);
    vector<vector<int>> tr(n + 1);
    for (int i = 1; i <= n; i++)
    {
        f[i] = i;
    }
    auto fin = [&](auto &&fin, int o) -> int
    {
        return o == f[o] ? o : f[o] = fin(fin, f[o]);
    };
    auto con = [&](int x, int y) -> void
    {
        x = fin(fin, x);
        y = fin(fin, y);
        f[x] = y;
    };
    for (int i = 1, x, y; i <= m; i++)
    {
        cin >> x >> y;
        e[i].first = x;
        e[i].second = y;
        tr[x].push_back(y);
        tr[y].push_back(x);
        con(x, y);
    }

    vector<int> siz(n + 1);
    vector<int> fa(n + 1);
    auto dfs = [&](auto &&self, int u, int f) -> void
    {
        siz[u] = 1;
        fa[u] = f;
        for (auto i : tr[u])
        {
            if (i == f)
            {
                continue;
            }
            self(self, i, u);
            siz[u] += siz[i];
        }
    };

    map<int, int> num;
    for (int i = 1; i <= n; i++)
    {
        num[fin(fin, i)]++;
    }
    int numa = 0, numb = 0;
    for (auto [a, b] : num)
    {
        dfs(dfs, a, 0);
        if (b % 2)
        {
            numa++;
        }
        else
        {
            numb++;
        }
    }
    // cout<<numa<<" "<<numb<<"\n";
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int a = numa;
        int b = numb;
        int tot = 0;
        if (num[fin(fin, i)] % 2)
        {
            a--;
        }
        else
        {
            b--;
        }
        for (auto j : tr[i])
        {
            // cout<<i<<'*'<<j<<"\n";
            if (j == fa[i])
            {
                continue;
            }
            if (siz[j] % 2)
            {
                a++;
            }
            else
            {
                b++;
            }
            tot += siz[j];
        }
        if ((num[fin(fin, i)] - tot - 1) % 2)
        {
            a++;
        }
        else if (num[fin(fin, i)] - tot - 1)
        {
            b++;
        }
        // cout<<i<<" "<<a<<" "<<b<<"\n";
        if (!(a % 2 || b % 2))
        {
            ans++;
        }
    }
    for (int i = 1; i < e.size(); i++)
    {
        auto &[x, y] = e[i];
        if (y == fa[x])
        {
            swap(x, y);
        }
        int a = numa;
        int b = numb;
        if (num[fin(fin, x)] % 2)
        {
            a--;
        }
        else
        {
            b--;
        }
        if (siz[y] % 2)
        {
            a++;
        }
        else
        {
            b++;
        }
        if ((num[fin(fin, x)] - siz[y]) % 2)
        {
            a++;
        }
        else if (num[fin(fin, x)] - siz[y])
        {
            b++;
        }
        if (!(a % 2 || b % 2))
        {
            ans++;
        }
    }
    cout << ans << "\n";
}
