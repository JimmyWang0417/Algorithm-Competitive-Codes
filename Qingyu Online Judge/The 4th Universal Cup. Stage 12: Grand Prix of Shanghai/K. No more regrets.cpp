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
struct Main
{
    int n, m;
    vector<i64> a;
    int block, num;
    vector<int> belong;
    vector<int> L, R;
    vector<vector<pair<i64, int>>> pmin, pmax;
    vector<vector<i64>> A, B;
    vector<vector<u64>> C;
    struct node
    {
        i64 k, b;
        node(i64 _k = 1, i64 _b = 0) : k(_k), b(_b) {}
        auto operator*(const node &rhs) const
        {
            return node(k * rhs.k, b * rhs.k + rhs.b);
        }
        auto operator*(const i64 &rhs) const
        {
            return k * rhs + b;
        }
    };
    vector<node> tag;
    auto pushup(int bl)
    {
        i64 minn = LLONG_MAX, maxx = LLONG_MIN;
        pmin[bl].clear(), pmax[bl].clear();
        A[bl].clear(), B[bl].clear(), C[bl].clear();
        for (int i = L[bl]; i <= R[bl]; ++i)
        {
            if (minn > a[i])
                pmin[bl].emplace_back(minn = a[i], i - L[bl]);
            if (maxx < a[i])
                pmax[bl].emplace_back(maxx = a[i], i - L[bl]);
            A[bl].push_back(minn);
            B[bl].push_back(maxx);
            C[bl].push_back((u64)minn * maxx);
        }
        pmin[bl].emplace_back(LLONG_MIN, R[bl] + 1 - L[bl]);
        pmax[bl].emplace_back(LLONG_MAX, R[bl] + 1 - L[bl]);
        partial_sum(A[bl].begin(), A[bl].end(), A[bl].begin());
        partial_sum(B[bl].begin(), B[bl].end(), B[bl].begin());
        partial_sum(C[bl].begin(), C[bl].end(), C[bl].begin());
    }
    auto pushdown(int bl)
    {
        for (int i = L[bl]; i <= R[bl]; ++i)
            a[i] = tag[bl] * a[i];
        tag[bl] = node();
    }
    auto query(int bl, i64 minn, i64 maxx)
    {
        if (tag[bl].k == 0)
        {
            minn = min(minn, tag[bl].b);
            maxx = max(maxx, tag[bl].b);
            return make_tuple((u64)minn * maxx * (R[bl] - L[bl] + 1), minn, maxx);
        }
        auto ad = tag[bl].b;
        int p = lower_bound(pmin[bl].begin(), pmin[bl].end(), make_pair(minn - ad, INT_MAX), greater<pair<i64, int>>())->second;
        int q = lower_bound(pmax[bl].begin(), pmax[bl].end(), make_pair(maxx - ad, 0))->second;
        u64 res = 0;
        auto calc = [](const auto &fuck, int l, int r)
        {
            auto ff = fuck[r];
            if (l)
                ff -= fuck[l - 1];
            return ff;
        };
        { // [0, min(p, q) - 1]
            res += (u64)minn * maxx * min(p, q);
        }
        { // [min(p, q), max(p, q) - 1]
            int be = min(p, q);
            int ed = max(p, q) - 1;
            if (p < q)
            {
                res += (u64)maxx * ad * (ed - be + 1);
                res += (u64)maxx * calc(A[bl], be, ed);
            }
            else if (p > q)
            {
                res += (u64)minn * ad * (ed - be + 1);
                res += (u64)minn * calc(B[bl], be, ed);
            }
        }
        { // [max(p, q), R[bl] - L[bl]]
            int be = max(p, q);
            int ed = R[bl] - L[bl];
            res += (u64)ad * ad * (ed - be + 1);
            res += (u64)ad * calc(A[bl], be, ed);
            res += (u64)ad * calc(B[bl], be, ed);
            res += (u64)calc(C[bl], be, ed);
        }
        return make_tuple(res, min(minn, ad + pmin[bl][pmin[bl].size() - 2].first), max(maxx, ad + pmax[bl][pmax[bl].size() - 2].first));
    }
    auto update(int l, int r, node val)
    {
        if (belong[l] == belong[r])
        {
            pushdown(belong[l]);
            for (int i = l; i <= r; ++i)
                a[i] = val * a[i];
            pushup(belong[l]);
            return;
        }

        pushdown(belong[l]);
        for (int i = l; i <= R[belong[l]]; ++i)
            a[i] = val * a[i];
        pushup(belong[l]);

        for (int i = belong[l] + 1; i < belong[r]; ++i)
            tag[i] = tag[i] * val;

        pushdown(belong[r]);
        for (int i = L[belong[r]]; i <= r; ++i)
            a[i] = val * a[i];
        pushup(belong[r]);
    }
    auto query(int l, int r)
    {
        if (belong[l] == belong[r])
        {
            i64 minn = LLONG_MAX, maxx = LLONG_MIN;
            u64 res = 0;
            for (int i = l; i <= r; ++i)
            {
                minn = min(minn, tag[belong[l]] * a[i]);
                maxx = max(maxx, tag[belong[l]] * a[i]);
                res += (u64)minn * maxx;
            }
            return res;
        }
        i64 minn = LLONG_MAX, maxx = LLONG_MIN;
        u64 res = 0;

        for (int i = l; i <= R[belong[l]]; ++i)
        {
            minn = min(minn, tag[belong[l]] * a[i]);
            maxx = max(maxx, tag[belong[l]] * a[i]);
            res += (u64)minn * maxx;
        }

        u64 _res;
        for (int i = belong[l] + 1; i < belong[r]; ++i)
        {
            tie(_res, minn, maxx) = query(i, minn, maxx);
            res += _res;
        }

        for (int i = L[belong[r]]; i <= r; ++i)
        {
            minn = min(minn, tag[belong[r]] * a[i]);
            maxx = max(maxx, tag[belong[r]] * a[i]);
            res += (u64)minn * maxx;
        }

        return res;
    }
    Main()
    {
        cin >> n >> m;
        a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        block = clamp((int)(sqrt(n * log2(n))), 1, n);
        num = (n - 1) / block + 1;
        belong.resize(n + 5);
        L.resize(num + 5), R.resize(num + 5);
        for (int i = 1; i <= num; ++i)
        {
            L[i] = R[i - 1] + 1;
            R[i] = min(R[i - 1] + block, n);
            for (int j = L[i]; j <= R[i]; ++j)
                belong[j] = i;
        }
        pmin.resize(num + 5), pmax.resize(num + 5);
        tag.resize(num + 5);
        A.resize(num + 5), B.resize(num + 5), C.resize(num + 5);
        for (int i = 1; i <= num; ++i)
            pushup(i);
        while (m--)
        {
            int opt, l, r, v;
            cin >> opt >> l >> r;
            if (opt == 1)
            {
                cin >> v;
                update(l, r, node(1, v));
            }
            else if (opt == 2)
            {
                cin >> v;
                update(l, r, node(0, v));
            }
            else
                cout << query(l, r) << '\n';
        }
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

