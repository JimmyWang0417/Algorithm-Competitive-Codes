#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

#define all(x) (x).begin(), (x).end()

template <class S>
inline bool updmn(S &x, const S y)
{
    if (y < x)
    {
        x = y;
        return 1;
    }
    return 0;
}

#define FAIL return void(cout << "-1\n")
struct Main
{
    static constexpr int inf = int(1e9);
    static constexpr int B = 15;
    int n;
    vector<int> a;
    vector<char> vis, indp;
    set<int> unvis;
    void main()
    {
        read();
        // trivial check
        if (n == 2 || n == 3)
            FAIL;
        for (int i = 2; i <= n; ++i)
        {
            if (isadj(a[i - 1], a[i]))
                FAIL;
        }
        int cnt_neg = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (a[i] == -1)
                ++cnt_neg;
        }
        if (cnt_neg)
        {
            greed();
            if (!maskdp())
                FAIL;
        }
        for (int i = 1; i <= n; ++i)
        {
            cout << a[i] << " \n"[i == n];
        }
    }
    bool isadj(const int x, const int y)
    {
        if (x == -1 || y == -1)
            return 0;
        return (x + 1 == y || y + 1 == x);
    }
    void read()
    {
        cin >> n;
        a.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
    }
    void greed()
    {
        vis.assign(n + 1, 0);
        int cnt_neg = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (a[i] == -1)
                ++cnt_neg;
            else
                vis[a[i]] = 1;
        }
        for (int x = 1; x <= n; ++x)
        {
            if (!vis[x])
                unvis.insert(x);
        }
        for (int i = 1; i <= n && cnt_neg > B; ++i)
        {
            if (a[i] != -1)
                continue;
            vector<int> banned;
            if (i - 1 >= 1)
            {
                banned.push_back(a[i - 1] - 1);
                banned.push_back(a[i - 1] + 1);
            }
            if (i + 1 <= n && a[i + 1] != -1)
            {
                banned.push_back(a[i + 1] - 1);
                banned.push_back(a[i + 1] + 1);
            }
            sort(all(banned));
            banned.erase(unique(all(banned)), banned.end());
            bool ok = 0;
            for (auto it = unvis.begin(); it != unvis.end(); ++it)
            {
                if (!binary_search(all(banned), *it))
                {
                    a[i] = *it;
                    unvis.erase(it);
                    ok = 1;
                    break;
                }
            }
            --cnt_neg;
            assert(ok);
        }
    }
    bool maskdp()
    {
        indp.assign(n + 1, 0);
        for (int i = n; i >= 1; --i)
        {
            if (a[i] == -1)
            {
                indp[i] = 1;
                if (i - 1 >= 1)
                    indp[i - 1] = 1;
                if (i + 1 <= n)
                    indp[i + 1] = 1;
            }
        }
        vector<int> b, pt, opt{all(unvis)};
        b.reserve(n);
        pt.reserve(B);
        int m = 0;
        for (int i = n; i >= 1; --i)
        {
            if (indp[i])
            {
                if (i + 1 <= n && !indp[i])
                    b.push_back(inf);
                b.push_back(a[i]);
                if (a[i] == -1)
                {
                    ++m;
                    pt.push_back(int(b.size()) - 1);
                }
            }
        }
#ifdef LOCAL
        dbg("m = %d\n", m);
        dbg("b: ");
        for (auto x : b)
            dbg("%d ", x);
        dbg("\n");
        dbg("pt: ");
        for (auto x : pt)
            dbg("%d ", x);
        dbg("\n");
#endif
        assert(m <= B);
        vector dp(1 << m, vector<int>(m, inf)); // pre
        for (int i = 0; i < m; ++i)
        {
            const int pos = 0;
            assert(b[pt[pos]] == -1);
            if (pt[pos] - 1 >= 0 && isadj(opt[i], b[pt[pos] - 1]))
                continue;
            if (pt[pos] + 1 < int(b.size()) && isadj(opt[i], b[pt[pos] + 1]))
                continue;
            dp[1 << i][i] = i;
        }
        for (int s = 1; s + 1 < (1 << m); ++s)
        {
            const int pos = __builtin_popcount(s);
            assert(b[pt[pos - 1]] == -1);
            for (int i = 0; i < m; ++i)
            {
                if (!(s >> i & 1))
                    continue;
                if (dp[s][i] == inf)
                    continue;
                for (int j = 0; j < m; ++j)
                {
                    if (i == j || (s >> j & 1))
                        continue;
                    const int ns = s | (1 << j);
                    dbg("s = %3d   opt[%d] = b[%d] = %3d   opt[%d] = b[%d] = %3d\n",
                        s, i, pt[pos - 1], opt[i], j, pt[pos], opt[j]);
                    if (pt[pos] - 1 >= 0)
                    {
                        if (pt[pos - 1] + 1 == pt[pos])
                        {
                            if (isadj(opt[j], opt[i]))
                                continue;
                        }
                        if (isadj(opt[j], b[pt[pos] - 1]))
                            continue;
                    }
                    if (pt[pos] + 1 < int(b.size()) && isadj(opt[j], b[pt[pos] + 1]))
                        continue;
                    updmn(dp[ns][j], i);
                }
            }
        }
        int s = (1 << m) - 1, u = -1;
        for (int i = 0; i < m; ++i)
        {
            if (dp[s][i] != inf)
            {
                u = i;
                break;
            }
        }
        if (u == -1)
            return 0;
        vector<int> order;
        order.reserve(m);
        while (s)
        {
            order.push_back(opt[u]);
            const int v = dp[s][u];
            s ^= (1 << u);
            u = v;
        }
#ifdef LOCAL
        dbg("order: ");
        for (auto x : order)
            dbg("%d ", x);
        dbg("\n");
#endif
        assert(int(order.size()) == m);
        for (int i = n; i >= 1; --i)
        {
            if (a[i] == -1)
            {
                a[i] = order.back();
                order.pop_back();
            }
        }
        return 1;
    }
};

signed main()
{
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    Main{}.main();
}
