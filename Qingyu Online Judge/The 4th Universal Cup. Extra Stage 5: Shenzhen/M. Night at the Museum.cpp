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
typedef complex<double> p2;
auto dot(p2 x, p2 y)
{
    return (conj(x) * y).real();
}
auto cross(p2 x, p2 y)
{
    return (conj(x) * y).imag();
}
constexpr double eps = 1e-9;
struct Main
{
    int n, m, r, ang;
    vector<p2> a, b;
    auto solve(double A, double B, double C) -> vector<double>
    {
        if (A < 0)
            A = -A, B = -B, C = -C;
        auto delta = B * B - 4 * A * C;
        if (delta < 0)
            return {};
        return {(-B - sqrt(delta)) / (2 * A), (-B + sqrt(delta)) / (2 * A)};
    }
    Main()
    {
        cin >> n >> m >> r >> ang;
        a.resize(n), b.resize(m);
        for (int i = 0; i < n; ++i)
        {
            int x, y;
            cin >> x >> y;
            a[i] = p2(x, y);
        }
        for (int i = 0; i < m; ++i)
        {
            int x, y;
            cin >> x >> y;
            b[i] = p2(x, y);
        }
        vector<double> answer(m + 1);
        for (int i = 0; i < n; ++i)
        {
            auto X = a[i], Y = a[(i + 1) % n];
            auto an = arg(Y - X) + ang / 180.0 * M_PI;
            auto Z = polar(1.0, an);
            vector<pair<double, double>> p;
            for (int j = 0; j < m; ++j)
            {
                if (cross(Y - X, b[j] - X) >= 0)
                {
                    auto V = solve(norm(Y - X), -2 * dot(Y - X, b[j] - X), norm(b[j] - X) - r * r);
                    if (!V.empty())
                    {
                        double L = max(V[0], 0.0);
                        double R = min({cross(b[j] - X, Z) / cross(Y - X, Z), V[1], 1.0});
                        if (L <= R)
                            p.emplace_back(L, R);
                    }
                }
            }
            an = arg(Y - X) - ang / 180.0 * M_PI;
            Z = polar(1.0, an);
            for (int j = 0; j < m; ++j)
            {
                if (cross(Y - X, b[j] - X) < 0)
                {
                    auto V = solve(norm(Y - X), -2 * dot(Y - X, b[j] - X), norm(b[j] - X) - r * r);
                    if (!V.empty())
                    {
                        double L = max(V[0], 0.0);
                        double R = min({cross(b[j] - X, Z) / cross(Y - X, Z), V[1], 1.0});
                        if (L <= R)
                            p.emplace_back(L, R);
                    }
                }
            }
            // for (auto [x, y] : p)
            //     cerr << x << ' ' << y << '\n';
            // cerr << '\n';
            vector<pair<double, int>> q;
            for (auto [x, y] : p)
            {
                q.emplace_back(x, 1);
                q.emplace_back(y, -1);
            }
            q.emplace_back(0, 0);
            q.emplace_back(1, 0);
            ranges::sort(q);
            auto len = abs(Y - X);
            for (int j = 0, k = 0; j < (int)q.size() - 1; ++j)
            {
                k += q[j].second;
                answer[k] += (q[j + 1].first - q[j].first) * len;
            }
        }
        cout << fixed << setprecision(9);
        for (int i = 0; i <= m; ++i)
            cout << answer[i] << '\n';
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

