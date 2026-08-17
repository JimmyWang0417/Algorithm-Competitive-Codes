#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 2e5 + 5;
constexpr int mod = 1e9 + 7;
int w, h, q;
vector<int> tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
auto pushup(int rt)
{
    for (int i = 0; i < w; ++i)
        tree[rt][i] = tree[lc][tree[rc][i]];
}
auto build(int rt, int l, int r)
{
    tree[rt].resize(w);
    iota(tree[rt].begin(), tree[rt].end(), 0);
    if (l == r)
        return;
    int mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}
auto update(int rt, int l, int r, int pos, int val)
{
    if (l == r)
    {
        swap(tree[rt][val], tree[rt][val + 1]);
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        update(lc, l, mid, pos, val);
    else
        update(rc, mid + 1, r, pos, val);
    pushup(rt);
}
auto _main()
{
    cin >> w >> h >> q;
    build(1, 1, h);
    for (int i = 1; i <= q; ++i)
    {
        int y, x1, x2;
        cin >> y >> x1 >> x2;
        update(1, 1, h, y, min(x1, x2) - 1);
        vector<bool> vis(w);
        const auto &p = tree[1];
        int ans = w;
        for (int j = 0; j < w; ++j)
        {
            if (vis[j])
                continue;
            --ans;
            for (int k = j; !vis[k]; k = p[k])
                vis[k] = true;
        }
        cout << ans << '\n';
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas)
        _main();
    return 0;
}
