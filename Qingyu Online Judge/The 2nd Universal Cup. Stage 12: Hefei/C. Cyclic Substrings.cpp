#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using i64 = int64_t;
constexpr int mod = 998244353;
struct Main
{
    struct pam
    {
        int tot;
        struct node
        {
            int ch[10];
            int fail, len;
            int add;
        };
        vector<node> point;
        vector<vector<int>> G;
        vector<int> dep;
        auto calc(int u, int _fa) -> i64
        {
            dep[u] = dep[_fa] + 1;
            i64 res = 0;
            for (auto v : G[u])
            {
                (res += calc(v, u)) %= mod;
                dp[u] += dp[v];
            }
            (res += (i64)dp[u] * dp[u] % mod * point[u].len) %= mod;
            return res;
        }
        vector<int> dp;
        pam() = default;
        pam(const string &str) : point(2)
        {
            auto newnode = [&]()
            {
                point.emplace_back();
                return (int)point.size() - 1;
            };
            point[0].fail = 1;
            point[1].len = -1;
            vector<int> p;
            int FUCK = (int)str.size() / 2;
            for (int n = 0, las = 1; n < (int)str.size(); ++n)
            {
                int c = str[n] - '0';
                auto find = [&](int now)
                {
                    while (n - point[now].len - 1 < 0 || str[n] != str[n - point[now].len - 1])
                        now = point[now].fail;
                    return now;
                };
                auto get = [&](int now, int len)
                {
                    now = point[find(now)].ch[c];
                    while (point[now].len > len)
                        now = point[now].fail;
                    return now;
                };
                int cur = find(las), now = point[cur].ch[c];
                if (!now)
                {
                    now = newnode();
                    point[now].len = point[cur].len + 2;
                    point[now].fail = point[find(point[cur].fail)].ch[c];
                    point[cur].ch[c] = now;
                    point[now].add = get(point[las].add, FUCK);
                }
                las = now;
                p.emplace_back(las);
            }
            tot = (int)point.size() - 1;
            G.resize(tot + 5);
            for (int i = 2; i <= tot; ++i)
                G[point[i].fail].emplace_back(i);
            dep.resize(tot + 5);
            dp.resize(tot + 5);
            for (int i = FUCK; i < (int)str.size(); ++i)
            {
                // cout << i << ": " << point[p[i]].add << ':';
                // for (int j = p[i]; j >= 2; j = point[j].fail)
                //     cout << "(" << ' ' << j << ',' << point[j].len << ") ";
                // cout << '\n';
                dp[point[p[i]].add]++;
            }
            i64 res = 0;
            for (int i = 2; i <= tot; ++i)
            {
                if (dep[i])
                    continue;
                (res += calc(i, 0)) %= mod;
            }
            cout << (res + mod) % mod << '\n';
        }
    };
    int n;
    string s;
    Main()
    {
        cin >> n >> s;
        pam p(s + s);
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