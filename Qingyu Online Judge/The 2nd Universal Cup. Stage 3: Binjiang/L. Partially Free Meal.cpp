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
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
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
struct Main
{
    int n;
    struct node
    {
        int lc, rc;
        int sze;
        i64 sum;
    };
#define lc(rt) tree[rt].lc
#define rc(rt) tree[rt].rc
    vector<node> tree;
    auto newnode()
    {
        tree.emplace_back();
        return (int)tree.size() - 1;
    }
    auto update(int pre, int l, int r, int p, int v)
    {
        int rt = newnode();
        tree[rt] = tree[pre];
        tree[rt].sze++;
        tree[rt].sum += v;
        if (l == r)
            return rt;
        int mid = (l + r) >> 1;
        if (p <= mid)
            lc(rt) = update(lc(pre), l, mid, p, v);
        else
            rc(rt) = update(rc(pre), mid + 1, r, p, v);
        return rt;
    }
    auto kth(int rt, int l, int r, int k) -> i64
    {
        if (!rt)
            return 0;
        if (l == r)
            return tree[rt].sum / tree[rt].sze * k;
        int mid = (l + r) >> 1;
        if (k <= tree[lc(rt)].sze)
            return kth(lc(rt), l, mid, k);
        else
            return tree[lc(rt)].sum + kth(rc(rt), mid + 1, r, k - tree[lc(rt)].sze);
    }
    vector<int> root;
    vector<i64> answer;
    vector<pair<int, int>> a;
    auto query(int x, int y) -> i64
    {
        if (y > tree[root[x]].sze)
            return LLONG_MAX;
        return kth(root[x], 1, 1e9, y) + a[x].second;
    }
    auto solve(int l, int r, int L, int R)
    {
        if (l > r)
            return;
        if (l == r)
        {
            for (int i = L; i <= R; ++i)
                answer[l] = min(answer[l], query(i, l));
            return;
        }
        int mid = (l + r) >> 1;
        int p = -1;
        i64 &res = answer[mid];
        for (int i = L; i <= R; ++i)
        {
            auto now = query(i, mid);
            if (res > now)
            {
                res = now;
                p = i;
            }
        }
        solve(l, mid - 1, L, p);
        solve(mid + 1, r, p, R);
    }
    Main() : tree(1)
    {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i].first >> a[i].second;
        sort(a.begin(), a.end(), [](auto x, auto y)
             { return x.second < y.second; });
        answer.resize(n + 5, LLONG_MAX);
        root.resize(n);
        for (int i = 0; i < n; ++i)
            root[i] = update(i ? root[i - 1] : 0, 1, 1e9, a[i].first, a[i].first);
        solve(1, n, 0, n - 1);
        for (int i = 1; i <= n; ++i)
            cout << answer[i] << '\n';
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
