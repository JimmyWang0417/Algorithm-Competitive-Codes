#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5 + 5;
typedef long long ll;
struct point
{
    int x, y;
    point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    inline auto operator<(const point &rhs) const
    {
        return x == rhs.x ? y < rhs.y : x < rhs.x;
    }
    inline auto operator==(const point &rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
    inline auto operator+(const point &rhs) const
    {
        return point(x + rhs.x, y + rhs.y);
    }
    inline auto operator-(const point &rhs) const
    {
        return point(x - rhs.x, y - rhs.y);
    }
    inline auto operator*(const point &rhs) const
    {
        return (ll)x * rhs.x + (ll)y * rhs.y;
    }
    inline auto operator^(const point &rhs) const
    {
        return (ll)x * rhs.y - (ll)y * rhs.x;
    }
};
typedef vector<point> hull;
inline hull operator*(hull lhs, hull rhs)
{
    if (lhs.empty() || rhs.empty())
        return hull();
    hull res(lhs.size() + rhs.size() - 1);
    adjacent_difference(lhs.begin(), lhs.end(), lhs.begin());
    adjacent_difference(rhs.begin(), rhs.end(), rhs.begin());
    res[0] = lhs[0] + rhs[0];
    merge(lhs.begin() + 1, lhs.end(), rhs.begin() + 1, rhs.end(), res.begin() + 1, [](const point &_lhs, const point &_rhs)
          { return (_lhs ^ _rhs) < 0; });
    partial_sum(res.begin(), res.end(), res.begin());
    return res;
}
inline hull convexhull(hull it)
{
    if (it.empty())
        return hull();
    if (!is_sorted(it.begin(), it.end()))
        sort(it.begin(), it.end());
    it.erase(unique(it.begin(), it.end()), it.end());
    hull res;
    for (auto i : it)
    {
        while (res.size() > 1 && ((res[res.size() - 2] - res.back()) ^ (i - res.back())) <= 0)
            res.pop_back();
        res.push_back(i);
    }
    return res;
}
inline hull operator+(hull lhs, hull rhs)
{
    if (lhs.empty())
        return rhs;
    if (rhs.empty())
        return lhs;
    vector<point> res(lhs.size() + rhs.size());
    merge(lhs.begin(), lhs.end(), rhs.begin(), rhs.end(), res.begin());
    return convexhull(res);
}
struct Tree
{
    int posf, posg;
    hull f, g;
    inline ll queryf(point val)
    {
        while (posf + 1 < (int)f.size() && f[posf] * val < f[posf + 1] * val)
            ++posf;
        return f[posf] * val;
    }
    inline ll queryg(point val)
    {
        while (posg + 1 < (int)g.size() && g[posg] * val < g[posg + 1] * val)
            ++posg;
        return g[posg] * val;
    }
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
    tree[rt].f = tree[lc].f * tree[rc].g + tree[rc].f;
    tree[rt].g = tree[lc].g * tree[rc].g;
}
inline void build(int rt, int l, int r)
{
    if (l == r)
    {
        tree[rt].f.clear(), tree[rt].g.clear();
        tree[rt].g.emplace_back(0, 0);
        if (l > 1)
        {
            int k;
            cin >> k;
            while (k--)
            {
                int x, y;
                cin >> x >> y;
                tree[rt].g.emplace_back(x, y);
            }
        }
        tree[rt].g = convexhull(tree[rt].g);
        int x, y;
        cin >> x >> y;
        tree[rt].f.emplace_back(x, y);
        return;
    }
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(rt);
}
inline int query(int rt, int l, int r, int pos, point val, ll &c)
{
    if (r <= pos)
    {
        if (tree[rt].queryf(val) < c)
        {
            c -= tree[rt].queryg(val);
            return -1;
        }
        if (l == r)
            return l;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        return query(lc, l, mid, pos, val, c);
    else
    {
        int res = query(rc, mid + 1, r, pos, val, c);
        if (res == -1)
            res = query(lc, l, mid, pos, val, c);
        return res;
    }
}
tuple<int, point, ll, int> que[N];
int n, m;
int answer[N];
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    build(1, 1, n);
    cin >> m;
    for (int i = 1; i <= m; ++i)
    {
        auto &[r, p, c, id] = que[i];
        cin >> r >> p.x >> p.y >> c;
        id = i;
    }
    sort(que + 1, que + 1 + m, [](const auto &lhs, const auto &rhs)
         { return (get<1>(lhs) ^ get<1>(rhs)) < 0; });
    for (int i = 1; i <= m; ++i)
    {
        auto [r, p, c, id] = que[i];
        answer[id] = query(1, 1, n, r, p, c);
    }
    for (int i = 1; i <= m; ++i)
        cout << answer[i] << '\n';
    return 0;
}