#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
constexpr int N = 4e5 + 5;
constexpr int mod = 998244353;
auto _main()
{
    int n, q;
    cin >> n >> q;
    struct node
    {
        int ch[2];
        int cnt;
        i64 sum;
    };
    vector<node> tree(1);
    tree.reserve(n * 50 + 5);
    auto newnode = [&]()
    {
        tree.emplace_back();
        return (int)tree.size() - 1;
    };
#define lc(rt) tree[rt].ch[0]
#define rc(rt) tree[rt].ch[1]
    auto update = [&](auto &&self, int &rt, int pre, int l, int r, int pos)
    {
        tree[rt = newnode()] = tree[pre];
        ++tree[rt].cnt, tree[rt].sum += pos;
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            self(self, lc(rt), lc(pre), l, mid, pos);
        else
            self(self, rc(rt), rc(pre), mid + 1, r, pos);
    };
    auto query = [&](auto &&self, int rt, int pre, int l, int r, int k)
    {
        if (l == r)
            return (tree[rt].sum - tree[pre].sum) / (tree[rt].cnt - tree[pre].cnt) * k;
        int mid = (l + r) >> 1;
        int cnt = tree[lc(rt)].cnt - tree[lc(pre)].cnt;
        if (k <= cnt)
            return self(self, lc(rt), lc(pre), l, mid, k);
        else
            return tree[lc(rt)].sum - tree[lc(pre)].sum + self(self, rc(rt), rc(pre), mid + 1, r, k - cnt);
    };
    vector<int> root(n + 5), a(n + 5);
    string s;
    cin >> s;
    for (int i = 1; i <= n; ++i)
        a[i] = a[i - 1] + (s[i - 1] == '1' ? 1 : -1);
    for (int i = 1; i <= n; ++i)
        update(update, root[i], root[i - 1], -n, n, a[i]);
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        cout << tree[root[r]].sum - tree[root[l - 1]].sum -
                    2 * query(query, root[r], root[l - 1], -n, n, (r - l + 1) / 2)
             << '\n';
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _main();
    return 0;
}
