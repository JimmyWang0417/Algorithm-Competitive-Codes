#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
struct Main
{
    int n, m;
    string s, t;
    vector<int> a;
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    array<int, 2> cnt = {};
    vector<vector<pair<int, int>>> tree;
    auto update(int rt, int l, int r, int x, int y, const pair<int, int> &val)
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
        {
            tree[rt].push_back(val);
            return;
        }
        int mid = (l + r) >> 1;
        update(lc, l, mid, x, y, val);
        update(rc, mid + 1, r, x, y, val);
    }
    vector<int> fa, sze, col;
    vector<pair<int, int>> st;
    auto print(int typ = 0)
    {
        for (int i = 0; i <= n; ++i)
            cout << find(i) << ' ';
        cout << '\n';
        if (typ)
        {
            for (int i = 0; i <= n; ++i)
                cout << col[find(i)] << ' ';
            cout << '\n';
        }
    }
    auto addst(const vector<pair<int, int>> &fuck)
    {
        for (auto [x, y] : fuck)
        {
            x = find(x), y = find(y);
            if (x == y)
                continue;
            if (sze[x] < sze[y])
                swap(x, y);
            cnt[col[x]]--, cnt[col[y]]--;
            fa[y] = x;
            col[x] ^= col[y];
            sze[x] += sze[y];
            cnt[col[x]]++;
            st.emplace_back(x, y);
        }
    }
    auto rollback(size_t lastop)
    {
        while (st.size() > lastop)
        {
            auto [x, y] = st.back();
            st.pop_back();
            cnt[col[x]]--;
            sze[x] -= sze[y];
            col[x] ^= col[y];
            fa[y] = y;
            cnt[col[x]]++, cnt[col[y]]++;
        }
    }
    auto find(int x) -> int
    {
        return fa[x] == x ? x : find(fa[x]);
    }
    vector<bool> answer;
    auto solve(int rt, int l, int r)
    {
        auto lastop = st.size();
        addst(tree[rt]);
        // cout << l << ' ' << r << ":\n";
        // for (auto [x, y] : tree[rt])
        //     cout << ' ' << x << ' ' << y << '\n';
        // print();
        if (l == r)
        {
            answer[l] = (cnt[1] == 0);
            rollback(lastop);
            return;
        }
        int mid = (l + r) >> 1;
        solve(lc, l, mid);
        solve(rc, mid + 1, r);
        rollback(lastop);
    }
    Main()
    {
        cin >> n >> m;
        cin >> s >> t;
        a.resize(n + 1);
        for (int i = 0; i < n; ++i)
            a[i] = (s[i] ^ t[i]);
        for (int i = n; i >= 1; --i)
            a[i] ^= a[i - 1];
        tree.resize(m * 4);
        for (int i = 1; i <= m; ++i)
        {
            int l, r;
            cin >> l >> r;
            // cout << i << ' ' << l - 1 << ' ' << r << '\n';
            update(1, 1, m, 1, i - 1, {l - 1, r});
            update(1, 1, m, i + 1, m, {l - 1, r});
        }
        fa.resize(n + 5), sze.resize(n + 5);
        iota(fa.begin(), fa.end(), 0);
        col = a;
        for (int i = 0; i <= n; ++i)
        {
            ++cnt[col[i]];
            sze[i] = 1;
        }
        answer.resize(m + 5);
        solve(1, 1, m);
        for (int i = 1; i <= m; ++i)
            cout << answer[i];
        cout << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
