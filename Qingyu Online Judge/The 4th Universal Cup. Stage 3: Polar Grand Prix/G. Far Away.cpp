#ifdef __FUCK_GCC
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("inline", "fast-math", "unroll-loops")
#endif
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <local/dbg.h>
#else
#define dbg(...) 42
#endif

using LL = long long;
#define ai(x) using ai##x = array<int, x>;
ai(2);
ai(3);
ai(4);
ai(5);
ai(6);
ai(7);
ai(8);
ai(9);
ai(10);
ai(26);
#undef ai

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()
template <typename T>
inline bool updmx(T &x, const T &y) { return x < y ? x = y, 1 : 0; }
template <typename T>
inline bool updmn(T &x, const T &y) { return y < x ? x = y, 1 : 0; }
template <typename T>
inline void clr(T &x) { T().swap(x); }

mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
LL rand(LL l, LL r) { return rng() % (r - l + 1) + l; }

struct DSU
{
    vector<int> fa, siz;
    DSU() {}
    DSU(int n)
    {
        init(n);
    }
    void init(int n)
    {
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
        siz.assign(n, 1);
    }
    int get(int x)
    {
        while (x != fa[x])
        {
            x = fa[x] = fa[fa[x]];
        }
        return x;
    }
    bool same(int x, int y)
    {
        return get(x) == get(y);
    }
    bool merge(int x, int y)
    {
        x = get(x), y = get(y);
        if (x == y)
            return 0;
        if (siz[y] > siz[x])
            swap(x, y);
        siz[x] += siz[y], fa[y] = x;
        return 1;
    }
    int size(int x)
    {
        return siz[get(x)];
    }
};

constexpr int N = 400;
constexpr int inf = 1e9;
constexpr int CK = 20000;

int main()
{
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> e(n + 1);
    DSU dsu(n + 1);
    for (int i = 0, u, v; i < m; ++i)
    {
        cin >> u >> v;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
        dsu.merge(u, v);
    }
    vector dis(N, vector<int>(n + 1, inf));
    auto bfs = [&](const int &_, const int &st) -> void
    {
        auto &d = dis[_];
        queue<int> p;
        p.push(st);
        d[st] = 0;
        while (p.size())
        {
            int u = p.front();
            p.pop();
            for (auto &v : e[u])
            {
                if (d[v] == inf)
                {
                    d[v] = d[u] + 1;
                    p.push(v);
                }
            }
        }
    };
    vector<int> pt(n);
    iota(all(pt), 1);
    shuffle(all(pt), rng);
    const int M = min(n, N);
    for (int i = 0; i < M; ++i)
        bfs(i, pt[i]);
    for (int x, y; q--;)
    {
        cin >> x >> y;
        if (!dsu.same(x, y))
        {
            cout << "YES\n";
            continue;
        }
        if (dsu.size(dsu.get(x)) <= CK + 1)
        {
            cout << "NO\n";
            continue;
        }
        bool ok = 0;
        for (int i = 0; i < M; ++i)
        {
            if (dis[i][x] + dis[i][y] <= CK)
            {
                ok = 1;
                break;
            }
        }
        if (!ok)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}

