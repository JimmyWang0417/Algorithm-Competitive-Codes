#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include <local/dbg.h>
#else
    #define dbg(...) 42
#endif

using i64 = long long;
using i128 = __int128;
using LL = long long;
using ai3 = array<int, 3>;
using ai26 = array<int, 26>;
struct segment {
    struct node {
        int lc, rc;
        int sze;
        i64 sum;
    };
    int n;
    vector<node> tree;
    auto newnode() {
        tree.emplace_back();
        return (int)tree.size() - 1;
    }
#define lc(rt) tree[rt].lc
#define rc(rt) tree[rt].rc
    auto update(int pre, int l, int r, int pos, int val) {
        int rt = newnode();
        tree[rt] = tree[pre];
        tree[rt].sze++;
        tree[rt].sum += val;
        if (l == r)
            return rt;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            lc(rt) = update(lc(pre), l, mid, pos, val);
        else
            rc(rt) = update(rc(pre), mid + 1, r, pos, val);
        return rt;
    }
    auto query(int rt, int l, int r, int x, int y) -> pair<int, i64> {
        if (r < x || l > y || !rt)
            return {0, 0};
        if (x <= l && r <= y)
            return {tree[rt].sze, tree[rt].sum};
        int mid = (l + r) >> 1;
        auto [x1, y1] = query(lc(rt), l, mid, x, y);
        auto [x2, y2] = query(rc(rt), mid + 1, r, x, y);
        return {x1 + x2, y1 + y2};
    }
    segment() = default;
    segment(int _n) : n(_n), tree(1) { tree.reserve(40 * _n); }
};
struct sam {
    struct node {
        int ch[26];
        int len, fail;
    };
    vector<node> point;
    int tot = 1, las = 1;
    vector<vector<int>> G;
    vector<int> dfn, low;
    int dfstime = 0;
    auto dfs(int u, int _fa) -> void {
        dfn[u] = ++dfstime;
        for (auto v : G[u]) {
            if (v == _fa)
                continue;
            dfs(v, u);
        }
        low[u] = dfstime;
    }
    vector<int> root;
    segment tree;
    sam() = default;
    sam(const string &s) : point(2) {
        auto insert = [&](int c) {
            auto newnode = [&]() {
                point.emplace_back();
                return (int)point.size() - 1;
            };
            int p = las, np = las = newnode();
            point[np].len = point[p].len + 1;
            for (; p && !point[p].ch[c]; p = point[p].fail)
                point[p].ch[c] = np;
            if (!p)
                point[np].fail = 1;
            else {
                int q = point[p].ch[c];
                if (point[q].len == point[p].len + 1)
                    point[np].fail = q;
                else {
                    int nq = newnode();
                    point[nq] = point[q];
                    point[nq].len = point[p].len + 1;
                    point[np].fail = point[q].fail = nq;
                    for (; p && point[p].ch[c] == q; p = point[p].fail)
                        point[p].ch[c] = nq;
                }
            }
            return np;
        };
        vector<int> p;
        for (auto c : s)
            p.emplace_back(insert(c - 'a'));
        tot = (int)point.size() - 1;
        // for (auto u : p)
        //     cout << ' ' << u;
        // cout << '\n';
        G.resize(tot + 5);
        dfn.resize(tot + 5), low.resize(tot + 5);
        for (int i = 2; i <= tot; ++i) {
            G[point[i].fail].push_back(i);
        }
        // for (int i = 1; i <= tot; ++i)
        //     cout << point[i].fail << ' ';
        // cout << '\n';
        dfs(1, 0);
        // for (int i = 1; i <= tot; ++i)
        //     cout << ' ' << dfn[i] << ' ' << low[i] << '\n';
        tree = segment(tot);
        root.resize(s.length() + 1);
        for (int i = 1; i <= (int)s.length(); ++i)
            root[i] = tree.update(root[i - 1], 1, tot, dfn[p[i - 1]], i);
    }
    auto query(int l, const string &s) {
        int u = 1;
        i128 res = 0;
        for (auto c : s) {
            u = point[u].ch[c - 'a'];
            if (!u)
                break;
            auto [x, y] = tree.query(root[l], 1, tot, dfn[u], low[u]);
            res += (i128)(l + 1) * x - y;
        }
        return res;
    }
};
struct Main {
    string T;
    int q;
    vector<string> p;
    void main() {
        cin >> T;
        sam t(T);
        cin >> q;
        while (q--) {
            int a;
            LL b;
            cin >> a >> b;
            p.resize(a);
            for (auto &s : p)
                cin >> s;
            auto check = [&](int mid) {
                i64 res = 0;
                for (const auto &s : p)
                    res += t.query(mid, s);
                return res >= b;
            };
            // cout << check(3) << '\n';
            int l = 0, r = (int)T.length();
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (check(mid))
                    r = mid - 1;
                else
                    l = mid + 1;
            }
            cout << (l == (int)T.length() + 1 ? -1 : l) << '\n';
        }
    }
};

int main() {
    // freopen("project.in", "r", stdin);
#ifndef LOCAL
    cin.tie(nullptr)
        ->sync_with_stdio(false);
#endif
    Main{}.main();
    return 0;
}