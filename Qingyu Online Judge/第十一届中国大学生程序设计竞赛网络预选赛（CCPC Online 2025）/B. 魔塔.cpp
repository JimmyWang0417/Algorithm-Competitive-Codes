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
    int n;
    vector<vector<int>> g;
    struct node
    {
        i64 round;
        int defence;
        i64 sum;
        node() = default;
        node(i64 _r, int _d, i64 _s) : round(_r), defence(_d), sum(_s) {}
        auto operator<(const node &rhs) const
        {
            return round * rhs.defence < rhs.round * defence;
        }
        auto operator>(const node &rhs) const
        {
            return rhs < (*this);
        }
        auto operator+(const node &rhs) const
        {
            return node(round + rhs.round, defence + rhs.defence, sum + (i64)defence * rhs.round + rhs.sum);
        }
    };
    vector<node> dp;
    vector<__gnu_pbds::priority_queue<node, greater<node>>> q;
    auto dfs(int u, int _fa) -> void
    {
        for (int v : g[u])
        {
            if (v == _fa)
                continue;
            dfs(v, u);
            q[u].join(q[v]);
        }
        if (u == 1 || (dp[u].round == 0 && dp[u].defence == 0))
            return;
        auto res = dp[u];
        while (!q[u].empty() && q[u].top() < res)
        {
            res = res + q[u].top();
            q[u].pop();
        }
        q[u].push(res);
    }
    Main()
    {
        int X;
        cin >> n >> X;
        g.resize(n + 5), dp.resize(n + 5);
        for (int i = 1; i < n; ++i)
        {
            int x, y;
            cin >> x >> y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        q.resize(n + 5);
        i64 sum = 0;
        for (int i = 2; i <= n; ++i)
        {
            int t, a, d, h;
            cin >> t;
            if (t == 1)
                dp[i] = node(0, 1, 0);
            else
            {
                cin >> a >> d >> h;
                dp[i] = node((h - 1) / (X - d), 0, 0);
                sum += (i64)a * dp[i].round;
            }
        }
        dfs(1, 0);
        node res(0, 0, 0);
        while (!q[1].empty())
        {
            res = res + q[1].top();
            q[1].pop();
        }
        cout << res.sum - sum << '\n';
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
