#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
typedef complex<double> p2; 
constexpr auto pi = M_PI;
auto cross(p2 x, p2 y)
{
    return (conj(x) * y).imag();
}
auto rotate(p2 x, double angle)
{
    return x * polar(1.0, angle);
}
struct Main
{
    Main()
    {
        int n, x0, y0, d;
        double t;
        cin >> n >> x0 >> y0 >> d >> t;
        double del = arg(p2(x0, y0));
        p2 L, R;
        for (int i = 0; i < n; ++i)
        {
            int x, y;
            cin >> x >> y;
            p2 p = rotate(p2(x, y), -del);
            double ang = arg(p2(sqrt(norm(p) - d * d), d));
            p2 l = rotate(p, -ang), r = rotate(p, ang);
            if (i == 0 || cross(l, L) >= 0)
                L = l;
            if (i == 0 || cross(R, r) >= 0)
                R = r;
        }
        auto calc = [](auto l, auto r, auto t)
        {
            int c = (int)floor(t / (2 * pi));
            auto res = (r - l) * c;
            t -= 2 * pi * c;
            return res + clamp(t - l, 0.0, r - l);
        };
        double Lang = arg(L), Rang = arg(R);
        if (Lang < 0)
            Lang += 2 * pi;
        if (Rang < 0)
            Rang += 2 * pi;
        cout << fixed << setprecision(6);
        if (Lang <= Rang)
            cout << calc(Lang, Rang, t) << '\n';
        else
            cout << calc(Lang, 2 * pi, t) + calc(0, Rang, t) << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}