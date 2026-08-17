#include <bits/stdc++.h>
struct node
{
    int l, r, x;
    node(int l1, int r1, int x1)
    {
        this->l = l1;
        this->r = r1;
        this->x = x1;
    }
};
using ll = long long;
void solve()
{
    int n;
    std::cin >> n;
    std::vector<int> l(n + 5), r(n + 5);
    for (int i = 1; i <= n; i++)
        std::cin >> l[i];
    for (int i = 1; i <= n; i++)
        std::cin >> r[i];
    std::vector<node> b;
    int l2 = -1, r2 = -1;
    for (int i = 1; i <= n; i++)
    {
        if (l[i] == r[i])
        {
            if (l2 != -1 && l[i] == l[i - 1])
                r2++;
            else
            {
                if (l2 != -1)
                    b.emplace_back(l2, r2, l[r2]);
                l2 = r2 = i;
            }
        }
        else
        {
            if (l2 != -1)
            {
                b.emplace_back(l2, r2, l[r2]);
            }
            l2 = r2 = -1;
        }
    }
    // std::cout<<l2<<' '<<r2<<'\n';
    if (l2 != -1)
        b.emplace_back(l2, r2, l[r2]);
    int m = (int)b.size();
    if (m == 0)
    {
        std::cout << n << '\n';
        return;
    }
    // std::cout<<m<<'\n';

    std::vector<std::vector<ll>> f(n + 5, std::vector<ll>(2, 1e12));
    ll ans = (ll)(b[0].l - 1) + (ll)(n - b[m - 1].r);
    f[0][0] = 0;
    auto check = [&](int l1, int r1)
    {
        // std::cout<<l1<<' '<<r1<<'\n';
        if (l1 > r1)
            return 1;
        else
        {
            for (int i = l1; i <= r1; i++)
                if (r[i] - l[i] >= 2)
                    return 1;
        }
        l1--;
        std::vector<std::vector<bool>> v(r1 - l1 + 1, std::vector<bool>(2));
        v[0][0] = v[0][1] = 1;
        for (int i = l1 + 1; i <= r1; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                for (int k = 0; k < 2; k++)
                {
                    int x = (j == 0 ? l[i - 1] : r[i - 1]), y = (k == 0 ? l[i] : r[i]);
                    if (x != y)
                        v[i - l1][k] = v[i - l1][k] | v[i - 1 - l1][j];
                }
            }
        }
        for (int j = 0; j < 2; j++)
        {
            int x = (j == 0 ? l[r1] : r[r1]);
            if (x != l[r1 + 1] && v[r1 - l1][j] == 1)
                return 1;
        }
        return 0;
    };
    // std::cout << m << '\n';
    for (int i = 1; i < m; i++)
    {
        if (check(b[i - 1].r + 1, b[i].l - 1))
        {
            // std::cout << "l r: " << b[i - 1].r << ' ' << b[i].l << '\n';
            f[i][0] = std::min(f[i - 1][0] + (ll)(b[i - 1].r - b[i - 1].l + 1) * (b[i - 1].r - b[i - 1].l + 1), f[i - 1][1] + (ll)(b[i - 1].r - b[i - 1].l + 2) * (b[i - 1].r - b[i - 1].l + 2)) + (ll)(b[i].l - b[i - 1].r - 1);
        }
        else
        {
            if (b[i].l - b[i - 1].r == 2)
            {
                f[i][0] = std::min(f[i - 1][0] + (ll)(b[i - 1].r - b[i - 1].l + 2) * (b[i - 1].r - b[i - 1].l + 2), f[i - 1][1] + (ll)(b[i - 1].r - b[i - 1].l + 3) * (b[i - 1].r - b[i - 1].l + 3));
                f[i][1] = std::min(f[i - 1][0] + (ll)(b[i - 1].r - b[i - 1].l + 1) * (b[i - 1].r - b[i - 1].l + 1), f[i - 1][1] + (ll)(b[i - 1].r - b[i - 1].l + 2) * (b[i - 1].r - b[i - 1].l + 2));
            }
            else
            {
                f[i][0] = std::min(std::min(f[i - 1][0] + (ll)(b[i - 1].r - b[i - 1].l + 1) * (b[i - 1].r - b[i - 1].l + 1), f[i - 1][1] + (ll)(b[i - 1].r - b[i - 1].l + 2) * (b[i - 1].r - b[i - 1].l + 2)) + 1 + b[i].l - b[i - 1].r, std::min(f[i - 1][0] + (ll)(b[i - 1].r - b[i - 1].l + 2) * (b[i - 1].r - b[i - 1].l + 2), f[i - 1][1] + (ll)(b[i - 1].r - b[i - 1].l + 3) * (b[i - 1].r - b[i - 1].l + 3)) + b[i].l - b[i - 1].r - 2);
                f[i][1] = std::min(f[i - 1][0] + (ll)(b[i - 1].r - b[i - 1].l + 1) * (b[i - 1].r - b[i - 1].l + 1) + b[i].l - b[i - 1].r - 2, f[i - 1][1] + (ll)(b[i - 1].r - b[i - 1].l + 2) * (b[i - 1].r - b[i - 1].l + 2) + b[i].l - b[i - 1].r - 2);
            }
        }
        // std::cout << f[i][0] << ' ' << f[i][1] << '\n';
    }
    std::cout << ans + std::min(f[m - 1][0] + (ll)(b[m - 1].r - b[m - 1].l + 1) * (b[m - 1].r - b[m - 1].l + 1), f[m - 1][1] + (ll)(b[m - 1].r - b[m - 1].l + 2) * (b[m - 1].r - b[m - 1].l + 2)) << '\n';
}
int main()
{
    int T;
    std::cin >> T;
    while (T--)
        solve();
}
