#include <bits/stdc++.h>
using namespace std;

int main()
{
    static const long long mod = 1000000007;
    static const int maxn = 30, maxm = 10;
    int n, m;
    static int d[maxm], msk[maxm][maxn];
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d", d + i);
    int p = 0;
    while (d[p] >= n)
        p++, m--;
    for (int i = 0; i < m; i++)
        d[i] = d[i + p];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {
            int r = j % d[i], x = 0;
            while (r < n)
                x ^= 1 << r, r += d[i];
            msk[i][j] = x;
        }
    struct node
    {
        int mx;
        long long cnt;
        inline node operator+(const node rhs) const
        {
            return {max(mx, rhs.mx), ((mx >= rhs.mx) * cnt + (rhs.mx >= mx) * rhs.cnt) % mod};
        }
    };
    function<node(const vector<int> &)> dfs = [&dfs, n, m](const vector<int> &v)
    {
        static unordered_map<int, node> dp;
        if (v[0] == (1 << n) - 1)
            return (node){0, 1};
        if (dp.count(v[0]))
            return dp[v[0]];
        node ret = {0, 0};
        for (int i = 0; i < d[0]; i++)
        {
            int p = i + __builtin_popcount(v[0] & msk[0][i]) * d[0];
            if (p >= n)
                continue;
            int cnt = 0;
            auto nxt = v;
            nxt[0] |= 1 << p;
            for (int r = 1; r < m; r++)
            {
                int s = nxt[r - 1] & msk[r][p];
                cnt += __builtin_popcount(s >> p) - 1;
                p = p % d[r] + (__builtin_popcount(s) - 1) * d[r];
                nxt[r] |= 1 << p;
            }
            node cur = dfs(nxt);
            cur.mx += cnt, ret = ret + cur;
        }
        return dp[v[0]] = ret;
    };
    int cnt = 0;
    for (int i = 0; i < d[0]; i++)
    {
        int pop = __builtin_popcount(msk[0][i]);
        cnt += pop * (pop - 1) >> 1;
    }
    vector<int> v(m);
    node ans = dfs(v);
    ans.mx += cnt, printf("%d %lld\n", ans.mx, ans.cnt);
    return 0;
}
