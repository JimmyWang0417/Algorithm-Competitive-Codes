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
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
    i64 res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
constexpr int N = 1.5e5 + 5;
constexpr int block = (450000 + 63) / 64;
struct Main
{
    int n, m, q;
    vector<int> a;
    vector<vector<int>> G;
    vector<tuple<int, int, int>> Q;
    Main()
    {
        cin >> n >> m;
        G.resize(n + 5);
        a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            cin >> u >> v;
            G[u].emplace_back(v);
        }
        cin >> q;
        Q.resize(q);
        for (auto &[o, x, y] : Q)
        {
            cin >> o >> x;
            if (o == 1)
                cin >> y;
        }
        int C = n;
        vector<int> deg(n + 5), order;
        queue<int> que;
        for (int x = 1; x <= n; ++x)
            for (auto y : G[x])
                ++deg[y];
        for (int i = 1; i <= n; ++i)
            if (!deg[i])
                que.emplace(i);
        while (!que.empty())
        {
            int x = que.front();
            que.pop();
            order.emplace_back(x);
            for (auto y : G[x])
                if (!--deg[y])
                    que.emplace(y);
        }
        int B = block;
        int cnt = (q + B - 1) / B;
        vector<vector<int>> point(cnt), color(cnt), occur(C + 5);
        vector<vector<pair<int, int>>> ask(cnt);
        vector<int> qid(q, -1), ans, now = a, cur, belong(C + 5, -1);
        vector<bool> vis(n + 5);
        for (int b = 0; b < cnt; ++b)
        {
            int L = b * B, R = min(L + B, q);
            cur = now;
            auto addpoint = [&](int x)
            {
                if (!vis[x])
                    vis[x] = true, point[b].emplace_back(x);
            };
            auto addcolor = [&](int x)
            {
                if (belong[x] == -1)
                    belong[x] = color[b].size(), color[b].emplace_back(x);
            };
            for (int i = L; i < R; ++i)
            {
                auto [o, x, y] = Q[i];
                if (o == 1)
                {
                    addpoint(x);
                    addcolor(cur[x]);
                    addcolor(y);
                    cur[x] = y;
                }
                else
                {
                    qid[i] = ans.size();
                    ask[b].emplace_back(x, ans.size());
                    ans.emplace_back(0);
                }
            }
            now = cur;
            for (auto x : point[b])
                vis[x] = false;
            for (auto x : color[b])
                belong[x] = -1, occur[x].emplace_back(b);
        }
        vector<bitset<block>> h(n + 1), hit(B);
        auto rebuild = [&](const vector<int> &b, const vector<int> &c, int l, int r, bool hide)
        {
            fill(h.begin(), h.end(), bitset<block>());
            for (int i = l; i < r; ++i)
                belong[c[i]] = i - l;
            for (int i = 1; i <= n; ++i)
                if ((!hide || !vis[i]) && belong[b[i]] != -1)
                    h[i].set(belong[b[i]]);
            for (auto it = order.rbegin(); it != order.rend(); ++it)
            {
                int x = *it;
                for (auto y : G[x])
                    h[x] |= h[y];
            }
        };
        auto clear = [&](const vector<int> &c, int l, int r)
        {
            for (int i = l; i < r; ++i)
                belong[c[i]] = -1;
        };
        vector<pair<int, int>> die;
        die.reserve(B);
        auto solve = [&](const vector<int> &c, int l, int r, int birth)
        {
            bitset<block> mask;
            die.clear();
            for (int i = l; i < r; ++i)
            {
                int p = i - l;
                mask.set(p);
                auto it = upper_bound(occur[c[i]].begin(), occur[c[i]].end(), birth);
                int d = it == occur[c[i]].end() ? cnt : *it;
                die.emplace_back(d, p);
            }
            sort(die.begin(), die.end());
            int p = 0, alive = r - l;
            for (int b = birth + 1; b < cnt && alive; ++b)
            {
                while (p < (int)die.size() && die[p].first <= b)
                {
                    int x = die[p++].second;
                    mask.reset(x);
                    --alive;
                }
                for (auto [x, id] : ask[b])
                    ans[id] += (h[x] & mask).count();
            }
        };
        vector<int> all(C);
        iota(all.begin(), all.end(), 1);
        for (int l = 0; l < C; l += B)
        {
            int r = min(l + B, C);
            rebuild(a, all, l, r, false);
            solve(all, l, r, -1);
            clear(all, l, r);
        }
        now = a;
        for (int b = 0; b < cnt; ++b)
        {
            int L = b * B, R = min(L + B, q);
            for (auto x : point[b])
                vis[x] = true;
            if (!point[b].empty())
            {
                fill(h.begin(), h.end(), bitset<block>());
                for (int i = 0; i < (int)point[b].size(); ++i)
                    h[point[b][i]].set(i);
                for (auto it = order.rbegin(); it != order.rend(); ++it)
                {
                    int x = *it;
                    for (auto y : G[x])
                        h[x] |= h[y];
                }
                for (int i = L; i < R; ++i)
                    if (get<0>(Q[i]) != 1)
                        hit[i - L] = h[get<1>(Q[i])];
            }
            for (int l = 0; l < (int)color[b].size(); l += B)
            {
                int r = min(l + B, (int)color[b].size());
                rebuild(now, color[b], l, r, true);
                cur = now;
                for (int i = L; i < R; ++i)
                {
                    auto [o, x, y] = Q[i];
                    if (o == 1)
                        cur[x] = y;
                    else
                    {
                        bitset<block> res = h[x];
                        for (int j = 0; j < (int)point[b].size(); ++j)
                            if (hit[i - L][j] && belong[cur[point[b][j]]] != -1)
                            {
                                int p = belong[cur[point[b][j]]];
                                res.set(p);
                            }
                        ans[qid[i]] += res.count();
                    }
                }
                clear(color[b], l, r);
            }
            for (int i = L; i < R; ++i)
            {
                auto [o, x, y] = Q[i];
                if (o == 1)
                    now[x] = y;
            }
            for (auto x : point[b])
                vis[x] = false;
            for (int l = 0; l < (int)color[b].size(); l += B)
            {
                int r = min(l + B, (int)color[b].size());
                rebuild(now, color[b], l, r, false);
                solve(color[b], l, r, b);
                clear(color[b], l, r);
            }
        }
        for (auto x : ans)
            cout << x << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}

