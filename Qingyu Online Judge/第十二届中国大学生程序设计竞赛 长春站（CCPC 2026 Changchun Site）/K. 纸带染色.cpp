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
#define allr(x) (x).rbegin(), (x).rend()

using LL = long long;
using ai2 = array<int, 2>;
using ai3 = array<int, 3>;

#define ls (p << 1)
#define rs (p << 1 | 1)
#define PP int mid = (q[p].l + q[p].r) >> 1
template <class S, auto op, auto e>
struct _SGT
{ // acl-like segtree
private:
    struct Node
    {
        int l, r;
        S s;
    };
    vector<Node> q;
    void pull(int p) { q[p].s = op(q[ls].s, q[rs].s); }
    void build(const vector<S> &a, int l, int r, int p = 1)
    {
        q[p].l = l, q[p].r = r;
        if (l == r)
            return (void)(q[p].s = a[l]);
        int mid = (l + r) >> 1;
        build(a, l, mid, ls);
        build(a, mid + 1, r, rs);
        pull(p);
    }

public:
    _SGT(int n) { init(n); }
    _SGT(const vector<S> &a, int n) { init(a, n); }
    void init(int n) { init(vector<S>(n + 1, e()), n); }
    void init(const vector<S> &a, int n)
    {
        q.resize(n * 4 + 10);
        build(a, 1, n);
    }
    S query(int l, int r, int p = 1)
    {
        if (q[p].l == l && q[p].r == r)
            return q[p].s;
        PP;
        if (r <= mid)
            return query(l, r, ls);
        else if (l > mid)
            return query(l, r, rs);
        else
            return op(query(l, mid, ls), query(mid + 1, r, rs));
    }
    void set(int x, S s, int p = 1)
    {
        if (q[p].l == q[p].r)
            return (void)(q[p].s = s);
        PP;
        set(x, s, x <= mid ? ls : rs);
        pull(p);
    }
    S at(int x, int p = 1)
    {
        if (q[p].l == q[p].r)
            return q[p].s;
        PP;
        return at(x, x <= mid ? ls : rs);
    }
};
#undef PP
#undef ls
#undef rs

constexpr int inf = int(1e9) + 7;
namespace def
{
    using S = int;
    S op(S a, S b) { return a + b; }
    S e() { return 0; }
    using SGT = _SGT<S, op, e>;
};
using def::SGT;

namespace ST_C
{ // Sparse Table Constant
    static constexpr int N = int(5e5) + 5;
    int Logn[N];
    const bool __init = []() -> bool
    {
        Logn[1] = 0, Logn[2] = 1;
        for (int i = 3; i < N; i++)
        {
            Logn[i] = Logn[i / 2] + 1;
        }
        return 1;
    }();
}
template <class T, auto op>
class ST
{
    using VT = vector<T>;
    using VVT = vector<VT>;
    VVT a;

public:
    ST() {}
    ST(const vector<T> &v, int n)
    {
        init(v, n); // v is 1-index
    }
    void init(const vector<T> &v, int n)
    {
        int mx_l = ST_C::Logn[n] + 1; // max log
        a.assign(n + 1, VT(mx_l, T{}));
        for (int i = 1; i <= n; i++)
        {
            a[i][0] = v[i];
        }
        for (int j = 1; j < mx_l; j++)
        {
            int p = (1 << (j - 1));
            for (int i = 1; i + p <= n; i++)
            {
                a[i][j] = op(a[i][j - 1], a[i + p][j - 1]);
            }
        }
    }
    T query(int l, int r)
    {
        int lt = r - l + 1;
        int p = ST_C::Logn[lt];
        return op(a[l][p], a[r - (1 << p) + 1][p]);
    }
};
using PII = pair<int, int>; // {l_mx, r_mn}
PII op(PII x, PII y)
{
    return PII{
        max(x.first, y.first),
        min(x.second, y.second)};
}

struct Main
{
    int n, m, Q;
    vector<pair<bool, int>> tip;
    vector<PII> a;
    vector<ai3> qry; // [l, r, id]
    vector<int> ans;

    vector<int> R;
    void main()
    {
        read();
        calc_R();
        calc_ans();
        for (auto x : ans)
            cout << x << "\n";
    }
    void read()
    {
        cin >> n >> m >> Q;
        tip.assign(m + 1, {});
        a.assign(m + 1, {});
        for (int i = 1; i <= m; ++i)
        {
            auto &[op, x] = tip[i];
            cin >> op >> x;
            if (op == 0)
                a[i] = {x, inf};
            else
                a[i] = {0, x};
        }
        qry.assign(Q, {});
        ans.assign(Q, -1);
        for (int i = 0; auto &[l, r, id] : qry)
        {
            cin >> l >> r;
            id = i++;
        }
    }
    void calc_R()
    {
        ST<PII, op> st(a, m);
        R.assign(m + 1, 0);
        R[m] = m;
        for (int i = 1; i < m; ++i)
        {
            const auto [op, x] = tip[i];
            int l = i + 1, r = m, opt = i;
            while (l <= r)
            {
                const int mid = (l + r) >> 1;
                const auto [l_mx, r_mn] = st.query(i + 1, mid);
                bool ok = 1;
                if (l_mx == n || r_mn == 1 || l_mx + 1 >= r_mn)
                    ok = 0;
                if (op == 0)
                {
                    if (l_mx >= x)
                        ok = 0;
                }
                else
                {
                    if (r_mn <= x)
                        ok = 0;
                }
                dbg("i=%d ok=%d query(%d, %d) = {%d, %d}\n", i, ok, i + 1, mid, l_mx, r_mn);
                if (ok)
                {
                    opt = mid;
                    l = mid + 1;
                }
                else
                    r = mid - 1;
            }
            R[i] = opt;
            dbg("R[%d] = %d\n", i, opt);
        }
    }
    void calc_ans()
    {
        vector<vector<ai2>> mp(m + 1);
        vector<vector<int>> del(m + 1);
        for (auto [l, r, id] : qry)
        {
            mp[r].push_back({l, id});
        }
        SGT sgt(m);
        for (int r = 1; r <= m; ++r)
        {
            sgt.set(r, 1);
            del[R[r]].push_back(r);
            for (auto [l, id] : mp[r])
            {
                ans[id] = sgt.query(l, m);
            }
            for (auto x : del[r])
            {
                sgt.set(x, 0);
            }
        }
    }
};
signed main()
{
#ifndef LOCAL
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
#endif
    Main{}.main();
    return 0;
}
