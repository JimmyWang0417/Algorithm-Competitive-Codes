#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
    #define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
    #define dbg(...) 42
#endif

#define all(x) (x).begin(), (x).end()
using LL = long long;
using i64 = int64_t;
#define NO return void(cout << "NO\n")
constexpr int mod = 998244353;
constexpr auto quickpow(i64 a, int b)
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
struct Main {
    int n, m, t;
    string s;
    vector<i64> dis;
    vector<int> cnt;
    vector<bool> vis;
    vector<vector<pair<int, int>>> G, H;
    vector<i64> dp;
    void main() {
        cin >> n >> m >> t >> s;
        G.resize(n + 5), H.resize(n + 5);
        for (int i = 0; i < m; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            G[u].emplace_back(v, w);
            H[v].emplace_back(u, w);
        }
        dis.resize(n + 5, LLONG_MAX);
        cnt.resize(n + 5);
        vis.resize(n + 5);
        dis[t] = 0;
        cnt[t] = 1;
        {
            priority_queue<pair<i64, int>, vector<pair<i64, int>>, greater<>> q;
            q.emplace(dis[t], t);
            while (!q.empty()) {
                int u = q.top().second;
                q.pop();
                if (vis[u])
                    continue;
                vis[u] = true;
                for (auto [v, w] : H[u]) {
                    if (dis[v] > dis[u] + w) {
                        dis[v] = dis[u] + w;
                        cnt[v] = cnt[u];
                        q.emplace(dis[v], v);
                    } else if (dis[v] == dis[u] + w)
                        (cnt[v] += cnt[u]) %= mod;
                }
            }
        }
        dp.resize(n + 5);
        vector<int> in(n + 5);
        for (int i = 1; i <= n; ++i)
            in[i] = (int)G[i].size();
        queue<int> q;
        q.push(t);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            // cout << u << '\n';
            if (s[u - 1] == '0')
            {
                for (auto [v, w] : G[u])
                    (dp[u] += dp[v] + w) %= mod;
                (dp[u] *= quickpow(G[u].size(), mod - 2)) %= mod;
            }
            else
            {
                for (auto [v, w] : G[u])
                    if (dis[v] + w == dis[u])
                        (dp[u] += (dp[v] + w) * cnt[v]) %= mod;
                (dp[u] *= quickpow(cnt[u], mod - 2)) %= mod;
            }
            // cout << u << ' ' << dp[u] << '\n';
            for (auto [v, w] : H[u])
                if (!--in[v])
                    q.push(v);
        }
        for (int i = 1; i <= n; ++i)
            cout << dp[i] << ' ';
        cout << '\n';
    }
};

int main() {
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int T = 1;
    // cin >> T;
    while (T--)
        Main{}.main();
    return 0;
}
