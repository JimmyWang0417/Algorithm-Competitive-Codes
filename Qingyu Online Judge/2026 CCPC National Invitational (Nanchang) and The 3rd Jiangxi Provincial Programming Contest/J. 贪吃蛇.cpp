#include <bits/stdc++.h>
using namespace std;
using f80 = long double;
using i64 = int64_t;
using p2 = complex<f80>;
constexpr f80 eps = 1e-14;
const f80 pi = acosl(-1.0);
auto dot(p2 x, p2 y)
{
    return (conj(x) * y).real();
}
auto cross(p2 x, p2 y)
{
    return (conj(x) * y).imag();
}
struct Main
{
    int n, m;
    vector<p2> a;
    vector<pair<p2, int>> b;
    Main()
    {
        cin >> n >> m;
        a.resize(n);
        for (int i = 0; i < n; ++i)
        {
            int x, y;
            cin >> x >> y;
            a[i] = p2(x, y);
        }
        sort(a.begin(), a.end(), [](auto x, auto y)
             {
            if (abs(cross(x, y)) < eps && dot(x, y) > 0)
                return norm(x) < norm(y);
            else
                return arg(x) < arg(y); });
        for (int i = 0; i < n; ++i)
        {
            if (!b.empty() && abs(cross(b.back().first, a[i])) < eps && dot(b.back().first, a[i]) > 0)
                b.back().first = a[i];
            else
                b.emplace_back(a[i], 0);
            b.back().second++;
        }
        multiset<f80> se;
        int tot = 0;
        f80 res = 1e18;
        n = (int)b.size();
        for (int i = 0, j = 0; i < n; ++i)
        {
            while (tot < m)
            {
                se.emplace(dot(b[j].first, b[j].first));
                tot += b[j].second;
                j = (j + 1) % n;
            }
            auto x = b[i].first, y = b[(j + n - 1) % n].first;
            f80 angle = arg(conj(x) * y);
            if (angle < 0)
                angle += 2 * pi;
            res = min(res, 0.5 * angle * *se.rbegin());
            se.erase(se.find(dot(b[i].first, b[i].first)));
            tot -= b[i].second;
        }
        cout << fixed << setprecision(10) << res << '\n';
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