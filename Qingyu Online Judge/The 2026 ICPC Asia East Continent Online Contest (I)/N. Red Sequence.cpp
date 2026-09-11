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
struct node
{
    int x, y, z;
};
struct fenwick
{
    int n;
    constexpr static auto lowbit = [](int x)
    {
        return x & (-x);
    };
    vector<int> c;
    fenwick() = default;
    fenwick(int _n) : n(_n), c(2 * _n + 2, INT_MIN / 2) {}
    auto update(int pos, int val)
    {
        pos += n + 1;
        for (int i = pos; i < (int)c.size(); i += lowbit(i))
            c[i] = max(c[i], val);
    }
    auto query(int pos)
    {
        pos += n + 1;
        int res = INT_MIN / 2;
        for (int i = pos; i >= 1; i -= lowbit(i))
            res = max(res, c[i]);
        return res;
    }
    auto clear(int pos)
    {
        pos += n + 1;
        for (int i = pos; i < (int)c.size(); i += lowbit(i))
            c[i] = INT_MIN / 2;
    }
};
struct Main
{
    int n;
    vector<node> p;
    vector<int> dp;
    fenwick tree;
    auto cdq(int l, int r)
    {
        if (l == r)
        {
            if (l - 1 >= 0)
                dp[l] = max(dp[l], dp[l - 1]);
            return;
        }
        int mid = (l + r) >> 1;
        cdq(l, mid);
        vector<node> A(p.begin() + l, p.begin() + mid + 1);
        vector<node> B(p.begin() + mid + 1, p.begin() + r + 1);
        auto cmp = [](const node &lhs, const node &rhs)
        {
            return make_pair(lhs.y, lhs.z) < make_pair(rhs.y, rhs.z);
        };
        sort(A.begin(), A.end(), cmp);
        sort(B.begin(), B.end(), cmp);
        {
            int i = 0, j = 0;
            while (i < (int)A.size() && j < (int)B.size())
            {
                if (cmp(B[j], A[i]))
                {
                    dp[B[j].x] = max(dp[B[j].x], tree.query(B[j].z) + B[j].x);
                    j++;
                }
                else
                {
                    tree.update(A[i].z, dp[A[i].x] - A[i].x);
                    i++;
                }
            }
            while (j < (int)B.size())
            {
                dp[B[j].x] = max(dp[B[j].x], tree.query(B[j].z) + B[j].x);
                j++;
            }
            for (i = 0; i < (int)A.size(); ++i)
                tree.clear(A[i].z);
        }
        cdq(mid + 1, r);
    }
    void main()
    {
        vector<int> r, y, b;
        cin >> n;
        r.resize(n + 5), y.resize(n + 5), b.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> r[i] >> y[i] >> b[i];
        for (int i = 1; i <= n; ++i)
        {
            r[i] += r[i - 1];
            y[i] += y[i - 1];
            b[i] += b[i - 1];
        }

        for (int i = 0; i <= n; ++i)
            p.emplace_back(i, r[i] - y[i], r[i] - b[i]);
        dp.resize(n + 5);
        tree = fenwick(n);
        cdq(0, n);
        cout << dp[n] << '\n';
    }
};

int main()
{
    // freopen("project.in", "r", stdin);
#ifndef LOCAL
    cin.tie(nullptr)
        ->sync_with_stdio(false);
#endif
    Main{}.main();
    return 0;
}
