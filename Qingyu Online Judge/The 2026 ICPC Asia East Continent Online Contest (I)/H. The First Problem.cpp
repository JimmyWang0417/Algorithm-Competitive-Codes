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
    auto query(vector<pair<int, int>> rt, i64 b) {
        i64 cnt = 0, sum = 0;
        for (auto [x, y] : rt) {
            cnt += tree[x].sze - tree[y].sze;
            sum += tree[x].sum - tree[y].sum;
        }
        if ((i128)(n + 1) * cnt - sum < b)
            return -1;
        int l = 1, r = n;
        cnt = sum = 0;
        while (l < r) {
            int mid = (l + r) >> 1;
            i64 xcnt = cnt, xsum = sum;
            for (auto [x, y] : rt) {
                xcnt += tree[lc(x)].sze - tree[lc(y)].sze;
                xsum += tree[lc(x)].sum - tree[lc(y)].sum;
            }
            if ((i128)(mid + 1) * xcnt - xsum >= b) {
                for (auto &[x, y] : rt)
                    x = lc(x), y = lc(y);
                r = mid;
            } else {
                cnt = xcnt, sum = xsum;
                for (auto &[x, y] : rt)
                    x = rc(x), y = rc(y);
                l = mid + 1;
            }
        }
        return l;
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
        tree = segment(s.length());
        root.resize(tot + 1);
        vector<int> pos(tot + 1);
        for (int i = 1; i <= (int)s.length(); ++i)
            pos[dfn[p[i - 1]]] = i;
        for (int i = 1; i <= tot; ++i) {
            root[i] = root[i - 1];
            if (pos[i])
                root[i] = tree.update(root[i], 1, s.length(), pos[i], pos[i]);
        }
    }
    auto insert(const string &s, vector<pair<int, int>> &rt) {
        int u = 1;
        for (auto c : s) {
            u = point[u].ch[c - 'a'];
            if (!u)
                break;
            rt.emplace_back(root[low[u]], root[dfn[u] - 1]);
        }
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
            vector<pair<int, int>> rt;
            for (const auto &s : p)
                t.insert(s, rt);
            cout << t.tree.query(rt, b) << '\n';
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
