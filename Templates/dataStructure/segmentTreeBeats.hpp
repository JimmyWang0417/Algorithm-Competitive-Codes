#include <algorithm>
#include <climits>
#include <cstdio>
#define ll long long
#define lll __int128
#define ull unsigned ll
#define lowbit(x) (x & (-x))
template <typename T>
inline void read(T &x)
{
    x = 0;
    char s = (char)getchar();
    bool f = false;
    while (!(s >= '0' && s <= '9'))
    {
        if (s == '-')
            f = true;
        s = (char)getchar();
    }
    while (s >= '0' && s <= '9')
    {
        x = (x << 1) + (x << 3) + s - '0';
        s = (char)getchar();
    }
    if (f)
        x = (~x) + 1;
}
template <typename T, typename... T1>
inline void read(T &x, T1 &...x1)
{
    read(x);
    read(x1...);
}
template <typename T>
inline void ckmin(T &x, T y)
{
    if (x > y)
        x = y;
}
template <typename T>
inline void ckmax(T &x, T y)
{
    if (x < y)
        x = y;
}
using namespace std;
constexpr int N = 5e5 + 5;
int n, m;
struct Tree
{
    int size;
    ll sum;
    int first, cnt, second, maxb;
    int add1, add2, add3, add4;
    inline void update(int val1, int val2, int val3, int val4)
    {
        sum += (ll)val1 * cnt + (ll)val2 * (size - cnt);
        ckmax(maxb, first + val3);
        first += val1;
        if (second > INT_MIN)
            second += val2;
        ckmax(add3, add1 + val3);
        ckmax(add4, add2 + val4);
        add1 += val1, add2 += val2;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].sum = tree[lc].sum + tree[rc].sum;
    if (tree[lc].first > tree[rc].first)
    {
        tree[rt].first = tree[lc].first;
        tree[rt].cnt = tree[lc].cnt;
        tree[rt].second = max(tree[lc].second, tree[rc].first);
    }
    else if (tree[lc].first < tree[rc].first)
    {
        tree[rt].first = tree[rc].first;
        tree[rt].cnt = tree[rc].cnt;
        tree[rt].second = max(tree[lc].first, tree[rc].second);
    }
    else
    {
        tree[rt].first = tree[lc].first;
        tree[rt].cnt = tree[lc].cnt + tree[rc].cnt;
        tree[rt].second = max(tree[lc].second, tree[rc].second);
    }
    tree[rt].maxb = max(tree[lc].maxb, tree[rc].maxb);
}
inline void pushdown(int rt)
{
	int maxx = max(tree[lc].first, tree[rc].first);
    if (tree[lc].first == maxx)
        tree[lc].update(tree[rt].add1, tree[rt].add2, tree[rt].add3, tree[rt].add4);
    else
        tree[lc].update(tree[rt].add2, tree[rt].add2, tree[rt].add4, tree[rt].add4);

    if (tree[rc].first == maxx)
        tree[rc].update(tree[rt].add1, tree[rt].add2, tree[rt].add3, tree[rt].add4);
    else
        tree[rc].update(tree[rt].add2, tree[rt].add2, tree[rt].add4, tree[rt].add4);

    tree[rt].add1 = tree[rt].add2 = tree[rt].add3 = tree[rt].add4 = 0;
}
inline void build(int rt, int l, int r)
{
    tree[rt].size = r - l + 1;
    if (l == r)
    {
        read(tree[rt].maxb);
        tree[rt].sum = tree[rt].first = tree[rt].maxb;
        tree[rt].cnt = 1;
        tree[rt].second = INT_MIN;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline void update1(int rt, int l, int r, int x, int y, int val)
{
    if (r < x || l > y)
        return;
    if (x <= l && r <= y)
        return tree[rt].update(val, val, val, val);
    int mid = (l + r) >> 1;
    pushdown(rt);
    update1(lc, l, mid, x, y, val);
    update1(rc, mid + 1, r, x, y, val);
    pushup(rt);
}
inline void update2(int rt, int l, int r, int x, int y, int val)
{
    if (r < x || l > y || tree[rt].first <= val)
        return;
    if (x <= l && r <= y && tree[rt].second < val)
        return tree[rt].update(val - tree[rt].first, 0, val - tree[rt].first, 0);
    int mid = (l + r) >> 1;
    pushdown(rt);
    update2(lc, l, mid, x, y, val);
    update2(rc, mid + 1, r, x, y, val);
    pushup(rt);
}
inline ll query1(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return tree[rt].sum;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return query1(lc, l, mid, x, y) + query1(rc, mid + 1, r, x, y);
}
inline int query2(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return INT_MIN;
    if (x <= l && r <= y)
        return tree[rt].first;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return max(query2(lc, l, mid, x, y), query2(rc, mid + 1, r, x, y));
}
inline int query3(int rt, int l, int r, int x, int y)
{
    if (r < x || l > y)
        return INT_MIN;
    if (x <= l && r <= y)
        return tree[rt].maxb;
    int mid = (l + r) >> 1;
    pushdown(rt);
    return max(query3(lc, l, mid, x, y), query3(rc, mid + 1, r, x, y));
}
signed main()
{
    read(n, m);
    build(1, 1, n);
    for (int i = 1; i <= m; ++i)
    {
        int opt, x, y, z;
        read(opt, x, y);
        if (opt == 1)
        {
            read(z);
            update1(1, 1, n, x, y, z);
        }
        else if (opt == 2)
        {
            read(z);
            update2(1, 1, n, x, y, z);
        }
        else if (opt == 3)
            printf("%lld\n", query1(1, 1, n, x, y));
        else if (opt == 4)
            printf("%d\n", query2(1, 1, n, x, y));
        else if (opt == 5)
            printf("%d\n", query3(1, 1, n, x, y));
    }
    return 0;
}