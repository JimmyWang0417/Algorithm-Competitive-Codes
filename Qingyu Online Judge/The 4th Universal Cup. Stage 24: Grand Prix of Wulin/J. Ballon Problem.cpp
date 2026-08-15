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
struct Main
{
    struct node
    {
        int key, val, tim;
        int sze;
        int ch[2];
    };
    vector<node> tree;
#define lc(rt) tree[rt].ch[0]
#define rc(rt) tree[rt].ch[1]
    auto newnode(int c, int t)
    {
        static mt19937 rnd(114514);
        int u = (int)tree.size();
        tree.emplace_back(rnd(), c, t, 1);
        return u;
    }
    auto pushup(int rt)
    {
        tree[rt].sze = tree[lc(rt)].sze + tree[rc(rt)].sze + 1;
    }
    auto split(int rt, int sze, int &x, int &y) -> void
    {
        if (!rt)
            x = y = 0;
        else
        {
            if (sze <= tree[lc(rt)].sze)
            {
                y = rt;
                split(lc(rt), sze, x, lc(y));
            }
            else
            {
                x = rt;
                split(rc(rt), sze - tree[lc(rt)].sze - 1, rc(x), y);
            }
            pushup(rt);
        }
    }
    auto merge(int x, int y) -> int
    {
        if (!x || !y)
            return x | y;
        if (tree[x].key > tree[y].key)
        {
            rc(x) = merge(rc(x), y);
            pushup(x);
            return x;
        }
        else
        {
            lc(y) = merge(x, lc(y));
            pushup(y);
            return y;
        }
    }
    int row = 0, col = 0;
    auto insertR(int x, int y, int t)
    {
        int A, B;
        split(row, x, A, B);
        row = merge(merge(A, newnode(y, t)), B);
    }
    auto insertC(int x, int y, int t)
    {
        int A, B;
        split(col, x, A, B);
        col = merge(merge(A, newnode(y, t)), B);
    }
    auto queryR(int x) -> pair<int, int>
    {
        int A, B, C;
        split(row, x - 1, A, C);
        split(C, 1, B, C);
        pair<int, int> ans = {tree[B].val, tree[B].tim};
        row = merge(merge(A, B), C);
        return ans;
    }
    auto queryC(int x) -> pair<int, int>
    {
        int A, B, C;
        split(col, x - 1, A, C);
        split(C, 1, B, C);
        pair<int, int> ans = {tree[B].val, tree[B].tim};
        col = merge(merge(A, B), C);
        return ans;
    }
    auto query(int x, int y)
    {
        auto [A, B] = queryR(x);
        auto [C, D] = queryC(y);
        if (B > D)
            return A;
        else
            return C;
    }
    Main() : tree(1)
    {
        int q, c;
        cin >> q >> c;
        insertR(1, c, 0);
        insertC(1, c, 0);
        for (int i = 1; i <= q; ++i)
        {
            int opt, x, y;
            cin >> opt >> x >> y;
            if (opt == 1)
                insertR(x, y, i);
            else if (opt == 2)
                insertC(x, y, i);
            else
                cout << query(x, y) << '\n';
        }
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
