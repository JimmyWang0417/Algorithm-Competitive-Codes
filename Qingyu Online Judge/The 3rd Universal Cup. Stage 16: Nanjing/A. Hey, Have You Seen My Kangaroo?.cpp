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
    int n, m, q;
    string seq;
    vector<string> a;
    auto calc(int x, int y, int c)
    {
        if (c == 'U')
        {
            if (a[x - 1][y] == '1')
                --x;
        }
        else if (c == 'D')
        {
            if (a[x + 1][y] == '1')
                ++x;
        }
        else if (c == 'L')
        {
            if (a[x][y - 1] == '1')
                --y;
        }
        else
        {
            if (a[x][y + 1] == '1')
                ++y;
        }
        return make_pair(x, y);
    }
    auto to(int x, int y)
    {
        for (int i = 0; i < q; ++i)
        {
            int c = seq[i];
            if (c == 'U')
            {
                if (a[x - 1][y] == '1')
                    --x;
            }
            else if (c == 'D')
            {
                if (a[x + 1][y] == '1')
                    ++x;
            }
            else if (c == 'L')
            {
                if (a[x][y - 1] == '1')
                    --y;
            }
            else
            {
                if (a[x][y + 1] == '1')
                    ++y;
            }
        }
        return make_pair(x, y);
    }
    auto trans(int x) { return make_pair((x - 1) / m + 1, (x - 1) % m + 1); }
    auto trans(int x, int y) { return (x - 1) * m + y; }
    auto trans(const pair<int, int> &x) { return trans(x.first, x.second); }
    vector<int> p, dis;
    auto topo()
    {
        dis.assign(n * m + 5, -1);
        vector<int> in(n * m + 5);
        for (int i = 1; i <= n * m; ++i)
        {
            auto [x, y] = trans(i);
            if (a[x][y] == '1')
            {
                dis[i] = 0;
                ++in[p[i]];
            }
        }
        queue<int> que;
        for (int i = 1; i <= n * m; ++i)
        {
            auto [x, y] = trans(i);
            if (a[x][y] == '1')
                if (!in[i])
                    que.push(i);
        }
        while (!que.empty())
        {
            int u = que.front();
            que.pop();
            dis[p[u]] = max(dis[p[u]], dis[u] + 1);
            if (!--in[p[u]])
                que.push(p[u]);
        }
        for (int i = 1; i <= n * m; ++i)
        {
            auto [x, y] = trans(i);
            if (a[x][y] == '1')
                if (in[i])
                    dis[i] = INT_MAX;
        }
    }
    vector<list<int>> g;
    auto calculation()
    {
        vector las(n + 5, vector<int>(m + 5, -1));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (a[i][j] == '1')
                    las[i][j] = dis[trans(i, j)];
        g.resize(q);
        for (int i = 0; i < q; ++i)
        {
            vector now(n + 5, vector<int>(m + 5, -1));
            for (int j = 1; j <= n; ++j)
                for (int k = 1; k <= m; ++k)
                {
                    if (las[j][k] == -1)
                        continue;
                    auto [x, y] = calc(j, k, seq[i]);
                    if (now[x][y] == -1)
                        now[x][y] = las[j][k];
                    else if (las[j][k] <= now[x][y])
                        g[i].push_back(las[j][k]);
                    else
                    {
                        g[i].push_back(now[x][y]);
                        now[x][y] = las[j][k];
                    }
                }
            las = now;
            g[i].sort();
        }
    }
    Main()
    {
        cin >> n >> m >> q >> seq;
        a.resize(n + 5);
        a[0] = a[n + 1] = string(m + 2, '0');
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
            a[i] = '0' + a[i] + '0';
        }
        p.resize(n * m + 5);
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                if (a[i][j] == '1')
                    p[trans(i, j)] = trans(to(i, j));
        topo();
        calculation();
        vector<int> have(n * m + 1);
        for (int i = 1; i <= n * m; ++i)
        {
            if (dis[i] == -1)
                continue;
            ++have[min(dis[i], n * m)];
        }
        for (int i = n * m - 1; i >= 0; --i)
            have[i] += have[i + 1];
        vector<int> c(n * m + 5, INT_MAX);
        for (int i = 0; i < n * m; ++i)
        {
            int res = have[i];
            c[have[i]] = min(c[have[i]], i * q);
            for (int j = 0; j < q; ++j)
            {
                while (!g[j].empty() && g[j].front() < i)
                    g[j].pop_front();
                res -= (int)g[j].size();
                c[res] = min(c[res], i * q + j + 1);
            }
        }
        for (int i = 1; i <= n * m; ++i)
        {
            c[i] = min(c[i - 1], c[i]);
            cout << (c[i] == INT_MAX ? -1 : c[i]) << '\n';
        }
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
