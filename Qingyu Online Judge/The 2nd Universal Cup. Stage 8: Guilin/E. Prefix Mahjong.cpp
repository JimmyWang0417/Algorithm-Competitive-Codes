#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
constexpr auto LIM = 18;
struct matrix : array<int, LIM>
{
    using array<int, LIM>::array;
    static auto I()
    {
        matrix res;
        for (int i = 0; i < LIM; ++i)
            res[i] = 1 << i;
        return res;
    }
    auto friend operator*(const matrix &lhs, const matrix &_)
    {
        matrix rhs{};
        for (int i = 0; i < LIM; ++i)
            for (int j = 0; j < LIM; ++j)
                if ((_[i] >> j) & 1)
                    rhs[j] |= 1 << i;
        matrix res{};
        for (int i = 0; i < LIM; ++i)
            for (int j = 0; j < LIM; ++j)
                res[i] |= (!!(lhs[i] & rhs[j])) << j;
        return res;
    }
    auto print()
    {
        for (int i = 0; i < LIM; ++i)
        {
            for (int j = 0; j < LIM; ++j)
                cout << ((at(i) >> j) & 1);
            cout << '\n';
        }
    }
};
matrix BASE;
int mp[3][3][2];
struct segment
{
    vector<matrix> tree;
    int n;
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    segment() = default;
    segment(int _n) : tree(4 * _n, BASE), n(_n) {}
    auto pushup(int rt)
    {
        tree[rt] = tree[lc] * tree[rc];
    }
    auto update(int rt, int l, int r, int pos, matrix val)
    {
        if (l == r)
        {
            tree[rt] = val;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(lc, l, mid, pos, val);
        else
            update(rc, mid + 1, r, pos, val);
        pushup(rt);
    }
    auto update(int pos, matrix val)
    {
        update(1, 0, n - 1, pos, val);
    }
    auto query()
    {
        return (tree[1][mp[0][0][0]] >> mp[0][0][1]) & 1;
    }
};
auto init()
{
    int tot = 0;
    for (int x = 0; x < 3; ++x)
        for (int y = 0; y < 3; ++y)
            for (int c = 0; c < 2; ++c)
                mp[x][y][c] = tot++;
    BASE[mp[0][0][0]] = 1 << mp[0][0][0];
    BASE[mp[0][0][1]] = 1 << mp[0][0][1];
}
struct Main
{
    int n, m;
    vector<int> a;
    vector<int> p;
    segment tree;
    auto get(int _x)
    {
        matrix res{};
        auto add = [&](int x, int y)
        {
            res[x] |= 1 << y;
        };
        for (int c = 0; c < 2; ++c)
            for (int y = 0; y < 3; ++y)
                for (int z = 0; z < 3; ++z)
                {
                    int x = _x - z;
                    if (x < 0 || x - y < 0)
                        continue;
                    add(mp[y][z][c], mp[(x - y) % 3][y][c]);
                }
        {
            for (int y = 0; y < 3; ++y)
                for (int z = 0; z < 3; ++z)
                {
                    int x = _x - z - 2;
                    if (x < 0 || x - y < 0)
                        continue;
                    add(mp[y][z][0], mp[(x - y) % 3][y][1]);
                }
        }
        return res;
    }
    Main()
    {
        cin >> n;
        a.resize(n);
        for (auto &i : a)
        {
            cin >> i;
            p.emplace_back(i - 2);
            p.emplace_back(i - 1);
            p.emplace_back(i);
        }
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());
        m = (int)p.size();
        for (int i = 0; i < n; ++i)
            a[i] = (int)(lower_bound(p.begin(), p.end(), a[i]) - p.begin());
        tree = segment(m);
        vector<int> cnt(m);
        for (int i = 0; i < n; ++i)
        {
            auto A = get(++cnt[a[i]]);
            tree.update(a[i], A);
            // cout << a[i] << ' ' << cnt[a[i]] << '\n';
            // tree.tree[1].print();
            cout << tree.query();
        }
        cout << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init();
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
