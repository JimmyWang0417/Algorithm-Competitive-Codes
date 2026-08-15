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
struct tarjan
{
    vector<vector<int>> g;
    vector<int> dfn, low, belong;
    int dfstime, color;
    stack<int> st;
    auto dfs(int u) -> void
    {
        dfn[u] = low[u] = ++dfstime;
        st.push(u);
        for (int v : g[u])
        {
            if (!dfn[v])
            {
                dfs(v);
                low[u] = min(low[u], low[v]);
            }
            else if (!belong[v])
                low[u] = min(low[u], dfn[v]);
        }
        if (dfn[u] == low[u])
        {
            belong[u] = ++color;
            while (st.top() != u)
            {
                belong[st.top()] = color;
                st.pop();
            }
            st.pop();
        }
    }
    tarjan() = default;
    tarjan(int n, const vector<pair<int, int>> &edges) : 
        g(n + 5), dfn(n + 5), low(n + 5), belong(n + 5), dfstime(0), color(0)
    {
        for (auto [u, v] : edges)
            g[u].push_back(v);
        for (int i = 1; i <= n; ++i)
            if (!dfn[i])
                dfs(i);
    }
};
struct Main
{
    int n, m;
    vector<int> fa, dfn, low, dep;
    vector<vector<int>> g;
    vector<tuple<int, int, int>> p;
    int dfstime;
    auto dfs(int u, int _fa) -> void
    {
        dep[u] = dep[_fa] + 1;
        dfn[u] = ++dfstime;
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            dfs(v, u);
        }
        low[u] = dfstime;
    }
    int cnt;
    vector<pair<int, int>> edges;
    vector<pair<int, int>> tree;
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    auto build(int rt, int l, int r)
    {
        tree[rt].first = ++cnt;
        tree[rt].second = ++cnt;
        if (l == r)
        {
            edges.emplace_back(tree[rt].first, get<2>(p[l]) + n);
            edges.emplace_back(get<2>(p[l]), tree[rt].second);
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        edges.emplace_back(tree[rt].first, tree[lc].first);
        edges.emplace_back(tree[rt].first, tree[rc].first);

        edges.emplace_back(tree[lc].second, tree[rt].second);
        edges.emplace_back(tree[rc].second, tree[rt].second);
    }
    auto update(int rt, int l, int r, int x, int y, int v)
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
        {
            edges.emplace_back(v, tree[rt].first);
            edges.emplace_back(tree[rt].second, v + n);
            return;
        }
        int mid = (l + r) >> 1;
        update(lc, l, mid, x, y, v);
        update(rc, mid + 1, r, x, y, v);
    }
    Main() : dfstime(0)
    {
        cin >> n;
        dep.resize(n + 5), fa.resize(n + 5);
        dfn.resize(n + 5), low.resize(n + 5);
        g.resize(n + 5);
        for (int i = 2; i <= n; ++i)
        {
            cin >> fa[i];
            g[fa[i]].push_back(i);
        }
        for (int i = 2; i <= n; ++i)
        {
            edges.emplace_back(i + n, fa[i]);
            edges.emplace_back(fa[i] + n, i);
        }
        dfn.resize(n + 5), low.resize(n + 5);
        dfs(1, 0);
        p.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            p[i] = make_tuple(dep[i], dfn[i], i);
        sort(p.begin() + 1, p.begin() + 1 + n);
        // for (int i = 1; i <= n; ++i)
        //     cout << get<0>(p[i]) << ' ' << get<1>(p[i]) << ' ' << get<2>(p[i]) << '\n';
        cnt = 2 * n;
        tree.resize(4 * n);
        build(1, 1, n);
        cin >> m;
        while (m--)
        {
            int x, y;
            cin >> x >> y;
            int l = (int)(lower_bound(p.begin() + 1, p.begin() + 1 + n, make_tuple(dep[x] + y, dfn[x], 0)) - p.begin());
            int r = (int)(lower_bound(p.begin() + 1, p.begin() + 1 + n, make_tuple(dep[x] + y, low[x] + 1, 0)) - p.begin() - 1);
            if (l <= r)
                update(1, 1, n, l, r, x);
        }
        // for (auto [u, v] : edges)
        //     cout << u << ' ' << v << '\n';
        auto belong = tarjan(cnt, edges).belong;
        for (int i = 1; i <= n; ++i)
            if (belong[i] == belong[i + n])
            {
                cout << "No\n";
                return;
            }
        vector<int> answer;
        for (int i = 1; i <= n; ++i)
            if (belong[i] < belong[i + n])
                answer.push_back(i);
        cout << "Yes\n";
        cout << answer.size() << '\n';
        for (auto i : answer)
            cout << i << ' ';
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
