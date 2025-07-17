#include <bits/stdc++.h>
using namespace std;

#define ONLINE
#ifndef ONLINE
char DEBUG_BUFFER[1000];
#define debug(...)                                                        \
    {                                                                     \
        sprintf(DEBUG_BUFFER, ##__VA_ARGS__);                             \
        cerr << "\033[1;36m" << DEBUG_BUFFER << "\033[0;2m" << "\033[0m"; \
    }
#else
#define debug(...) ;
#endif

using LL = long long;
using PII = pair<int, int>;

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()

#define FAST_IO                      \
    {                                \
        ios::sync_with_stdio(false); \
        cin.tie(nullptr);            \
    }
inline int read()
{
    static int x;
    cin >> x;
    return x;
}
inline LL readLL()
{
    static LL x;
    cin >> x;
    return x;
}
mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());

const LL inf = 1e18;
struct Node
{
    int u, dep;
    LL k, b;
    bool vis;
};

int main()
{
    FAST_IO;
    int n, m;
    cin >> n >> m;
    if (n == 1)
    {
        cout << 0;
        return 0;
    }
    vector<vector<Node>> e(n + 1);
    {
        bool ok = 1;
        vector<int> fa(n + 1);
        iota(all(fa), 0);
        auto get = [&](int x) -> int
        {
            while (fa[x] != x)
            {
                x = fa[x] = fa[fa[x]];
            }
            return x;
        };
        for (int i = 1, u, v; i <= m; i++)
        {
            cin >> u >> v;
            e[u].push_back({v, -1, -1, -1, 0});
            e[v].push_back({u, -1, -1, -1, 0});
            int fau = get(u), fav = get(v);
            if (fau == fav)
                ok = 0;
            else
                fa[fau] = fav;
        }
        if (!ok)
        {
            cout << "NIE";
            return 0;
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (e[i].size() > 3)
        {
            cout << "NIE";
            return 0;
        }
    }
    vector<int> mx_dep(n + 1);
    { // get dep
        vector<int> dep(n + 1);
        vector<vector<PII>> dp(n + 1);
        auto dfs = [&](auto &&self, int u, int fa) -> int
        {
            int res = dep[u] = dep[fa] + 1;
            for (int i = 0; i < e[u].size(); i++)
            {
                const int v = e[u][i].u;
                if (v == fa)
                    continue;
                dp[u].push_back({self(self, v, u), i});
                if (dp[u].size() > 2)
                {
                    sort(allr(dp[u]));
                    dp[u].pop_back();
                }
            }
            sort(allr(dp[u]));
            debug("u=%d ", u);
            for (auto [x, y] : dp[u])
                debug("{%d,%d} ", x, e[u][y].u);
            debug("\n");
            if (dp[u].size())
                res = max(res, dp[u][0].first);
            return res;
        };
        dfs(dfs, 1, 0);
        auto dfs2 = [&](auto &&self, int u, int fa, int arg) -> void
        {
            mx_dep[u] = arg;
            if (dp[u].size())
            {
                mx_dep[u] = max(mx_dep[u], dp[u][0].first - dep[u] + 1);
            }
            for (int i = 0; i < e[u].size(); i++)
            {
                const int v = e[u][i].u;
                if (v == fa)
                    continue;
                int tmp = arg;
                if (dp[u].size() && dp[u][0].second != i)
                {
                    tmp = max(tmp, dp[u][0].first - dep[u] + 1);
                }
                else if (dp[u].size() >= 2 && dp[u][0].second == i)
                {
                    tmp = max(tmp, dp[u][1].first - dep[u] + 1);
                }
                self(self, v, u, tmp + 1);
            }
        };
        dfs2(dfs2, 1, 0, 1);
        for (int i = 1; i <= n; i++)
        {
            debug("mx_dep[%d]=%d\n", i, mx_dep[i]);
        }
    }
    auto upd = [&](int u, int i, LL k, LL b) -> void
    {
        e[u][i].k = k;
        e[u][i].b = b;
    };
    auto dfs = [&](auto &&self, int u, int fa, int id) -> LL
    {
        vector<int> son; // record id
        for (int i = 0; i < e[u].size(); i++)
        {
            const int v = e[u][i].u;
            if (v == fa)
                continue;
            if (!e[u][i].vis)
            {
                e[u][i].vis = 1;
                self(self, v, u, i);
            }
            son.push_back(i);
        }
        assert(son.size() <= 2);
        debug("\tu=%d son.size()=%d\n", u, son.size());
        LL res = -1;
        if (son.empty())
        {
            assert(id != -1);
            upd(fa, id, 1, 0);
        }
        else if (son.size() == 1)
        {
            const int i = son[0];
            LL k = e[u][i].k * 2 + 1, b = e[u][i].b;
            if (id != -1)
            {
                upd(fa, id, k, b);
            }
            else
                res = e[u][i].k + e[u][i].b;
            debug("\t%d->%d \"1\" %lld %lld\n", fa, u, k, b);
        }
        else
        { // size==2
            int i = son[0], j = son[1];
            if (e[u][j].k < e[u][i].k)
            {
                swap(i, j);
            }
            // now e[u][i].k<=e[u][j].k
            LL k = (e[u][i].k + e[u][j].k) * 2 + 1;
            LL b = e[u][i].k + e[u][i].b + e[u][j].b;
            if (id != -1)
            {
                upd(fa, id, k, b);
            }
            else
                res = k + b;
            debug("\t%d->%d \"2\" %lld %lld\n", fa, u, k, b);
        }
        return res;
    };
    LL ans = inf;
    for (int i = 1; i <= n; i++)
    {
        if (e[i].size() == 1 && mx_dep[i] <= 33)
        {
            LL res = dfs(dfs, i, 0, -1);
            debug("start %d 1 %lld\n", i, res);
            ans = min(ans, res);
        }
        else if (e[i].size() == 2 && mx_dep[i] <= 32)
        {
            LL res = dfs(dfs, i, 0, -1);
            debug("start %d 2 %lld\n", i, res);
            ans = min(ans, res);
        }
    }
    if (ans == inf)
        cout << "NIE";
    else
        cout << ans;
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */