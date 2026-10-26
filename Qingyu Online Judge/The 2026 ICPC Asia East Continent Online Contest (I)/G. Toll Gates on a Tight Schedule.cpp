#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #include <local/dbg.h>
#else
    #define dbg(...) 42
#endif

// mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
mt19937_64 rng(42);

using u64 = unsigned long long;
using LL = long long;

using ai3 = array<int, 3>;
using ai26 = array<int, 26>;

#define all(x) (x).begin(), (x).end()

template <class T>
inline bool updmx(T &x, const T y) {
    if (x < y) {
        x = y;
        return 1;
    }
    return 0;
}

struct Main {
    int n, m;
    LL C;
    vector<LL> a;
    vector<vector<int>> e, e_inv;
    vector<int> layer;
    vector<vector<int>> nodes; // in layers
    int LAYER = -1;
    vector<vector<LL>> val_first, val_second;
    u64 ans = 0;
    void main() {
        read();
        if (n == 1) {
            if (a[1] <= C)
                cout << "1\n";
            else
                cout << "0\n";
            return;
        }
        if (!remake_e()) {
            cout << "0\n";
            return;
        }
#ifdef LOCAL
        for (int u = 1; u <= n; ++u) dbg(u, e[u]);
        for (int l = 0; l < int(nodes.size()); ++l) dbg(l, nodes[l]);
#endif
        split_layer();
        dbg(LAYER);
        val_first.assign(n + 1, {});
        calc_first_half();
        for (auto u : nodes[LAYER]) radix_sort(val_first[u]);
        val_second.assign(n + 1, {});
        calc_second_half();
        for (auto u : nodes[LAYER]) {
            radix_sort(val_second[u]);
            auto &&p = val_first[u];
            auto &&q = val_second[u];
            dbg(u, p);
            dbg(u, q);
            int j = int(q.size()) - 1;
            for (int i = 0; i < int(p.size()); ++i) {
                while (j >= 0 && p[i] + q[j] > C) --j;
                ans += u64(j + 1);
            }
        }
        cout << ans << "\n";
    }
    void read() {
        cin >> n >> m >> C;
        a.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) cin >> a[i];
        e.assign(n + 1, {});
        for (int i = 1; i <= m; ++i) {
            int u, v;
            cin >> u >> v;
            e[u].push_back(v);
        }
    }
    bool remake_e() {
        vector<vector<int>> adj(n + 1);
        auto &&dp = layer;
        dp.assign(n + 1, 0);
        dp[1] = 1;
        queue<int> p;
        p.push(1);
        while (p.size()) {
            const int u = p.front();
            p.pop();
            if (u == n) break;
            for (auto v : e[u]) {
                if (!dp[v]) {
                    dp[v] = dp[u] + 1;
                    if (dp[n] && dp[v] > dp[n]) continue;
                    p.push(v);
                }
                if (dp[v] == dp[u] + 1) {
                    adj[u].push_back(v);
                }
            }
        }
        if (dp[n] == 0) return 0;
        swap(e, adj);
        dbg(dp[n], dp);
        nodes.assign(dp[n], {});
        for (int u = 1; u <= n; ++u) {
            if (dp[u] == 0 || dp[u] > dp[n]) continue;
            dbg(nodes.size(), dp[u] - 1);
            nodes[--dp[u]].push_back(u);
        }
        e_inv.assign(n + 1, {});
        for (int u = 1; u <= n; ++u) {
            for (auto v : e[u]) {
                e_inv[v].push_back(u);
            }
        }
        return 1;
    }
    void split_layer() {
        using u128 = __uint128_t;
        vector<u128> pre(n + 1), suf(n + 1);
        pre[1] = 1;
        for (int l = 0; l < int(nodes.size()) - 1; ++l) {
            for (auto u : nodes[l]) {
                for (auto v : e[u]) {
                    pre[v] += pre[u];
                }
            }
        }
        suf[n] = 1;
        for (int l = int(nodes.size()) - 1; l > 0; --l) {
            for (auto u : nodes[l]) {
                for (auto v : e_inv[u]) {
                    suf[v] += suf[u];
                }
            }
        }
        u128 best = -1;
        for (int l = 0; l < int(nodes.size()); ++l) {
            u128 tot = 0;
            for (auto u : nodes[l]) tot += pre[u] + suf[u];
            if (tot < best) {
                best = tot;
                LAYER = l;
            }
        }
    }
    void dfsOne(int u, LL c) {
        c += a[u];
        if (c > C) return;
        if (layer[u] == LAYER) {
            val_first[u].push_back(c);
            return;
        }
        for (auto v : e[u]) {
            dfsOne(v, c);
        }
    }
    void calc_first_half() {
        dfsOne(1, 0ll);
    }
    void dfsTwo(int u, LL c) {
        c += a[u];
        if (c > C) return;
        if (layer[u] == LAYER) {
            val_second[u].push_back(c - a[u]);
            return;
        }
        for (auto v : e_inv[u]) {
            dfsTwo(v, c);
        }
    }
    void calc_second_half() {
        dfsTwo(n, 0ll);
    }
    void radix_sort(vector<LL> &v) {
        if (v.size() < (1 << 15)) {
            sort(all(v));
            return;
        }
        constexpr int B = 16;
        constexpr int S = 1 << B;
        vector<LL> tmp(v.size());
        vector<int> cnt(S);
        for (int shift = 0; shift < 48; shift += B) {
            fill(all(cnt), 0);
            for (auto x : v) ++cnt[u64(x) >> shift & (S - 1)];
            int sum = 0;
            for (auto &x : cnt) {
                const int c = x;
                x = sum;
                sum += c;
            }
            for (auto x : v) tmp[cnt[u64(x) >> shift & (S - 1)]++] = x;
            v.swap(tmp);
        }
    }
};

int main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    Main{}.main();
    return 0;
}
