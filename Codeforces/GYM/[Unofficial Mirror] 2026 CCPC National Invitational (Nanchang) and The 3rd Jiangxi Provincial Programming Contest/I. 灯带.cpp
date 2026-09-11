#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
struct Main
{
    int n, m;
    array<int, 3> a;
    struct node
    {
        int l, r;
        auto operator<(const node &rhs) const
        {
            return r - l < rhs.r - rhs.l;
        }
    };
    vector<node> b;
    vector<int> answer;
    auto solve()
    {
        array<int, 3> p = {0, 1, 2};
        do
        {
            auto c = a;
            vector<int> d(b.size());
            for (int i = 0; i < (int)b.size(); ++i)
                d[i] = b[i].r - b[i].l + 1;
            bool flag = true;
            for (int i = 0, j = 0; i < (int)b.size(); ++i)
            {
                int k = j;
                while (c[p[k]] < d[i])
                    d[i] -= c[p[k++]];
                c[p[k]] -= d[i];
                if (k - j + !!d[i] == 3)
                {
                    flag = false;
                    break;
                }
                if (c[p[k]] == 0)
                    ++k;
                j = k;
            }
            if (flag)
            {
                c = a;
                for (int i = 0; i < (int)b.size(); ++i)
                    d[i] = b[i].r - b[i].l + 1;
                for (int i = 0, j = 0; i < (int)b.size(); ++i)
                {
                    int k = j;
                    while (c[p[k]] < d[i])
                    {
                        for (int l = 0; l < c[p[k]]; ++l)
                            answer[b[i].l++] = p[k];
                        d[i] -= c[p[k]];
                        c[p[k++]] = 0;
                    }
                    for (int l = 0; l < d[i]; ++l)
                        answer[b[i].l++] = p[k];
                    c[p[k]] -= d[i];
                    if (c[p[k]] == 0)
                        ++k;
                    j = k;
                }
                return true;
            }
        } while (next_permutation(p.begin(), p.end()));
        return false;
    }
    Main()
    {
        cin >> n >> m;
        b.resize(m);
        for (auto &i : a)
            cin >> i;
        for (auto &[l, r] : b)
            cin >> l >> r;
        vector<bool> vis(n + 5);
        for (auto [l, r] : b)
            for (int i = l; i <= r; ++i)
                vis[i] = true;
        for (int i = 1; i <= n; ++i)
        {
            if (vis[i])
                continue;
            b.emplace_back(i, i);
        }
        sort(b.begin(), b.end());
        answer.resize(n + 5, -1);
        if (solve())
        {
            for (int i = 1; i <= n; ++i)
                cout << (answer[i] == 0 ? 'R' : (answer[i] == 1 ? 'G' : 'B'));
            cout << '\n';
        }
        else
            cout << "-1\n";
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