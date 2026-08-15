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
    double x, y;
    int vx, vy;
    int y1, y2, vy1, vy2;
    int x1, x2, vx1, vx2;
    Main()
    {
        cin >> x >> y >> vx >> vy;
        cin >> y1 >> y2 >> vy1 >> vy2;
        cin >> x1 >> x2 >> vx1 >> vx2;
        double t = (double)(y2 - y1) / (vy1 + vy2);
        y = y1 + t * vy1;
        auto calc = [&]()
        {
            double nowt = 0;
            while (true)
            {
                double t1 = (double)(x1 - nowt * vx1 - x) / (vx + vx1) + nowt,
                       t2 = (double)(x2 + nowt * vx2 - x) / (vx - vx2) + nowt;
                if (t1 <= nowt)
                    t1 = 1e18;
                if (t2 <= nowt)
                    t2 = 1e18;
                if (t1 >= t && t2 >= t)
                    return x + (t - nowt) * vx;
                else if (t1 < t2)
                {
                    nowt = t1;
                    x = x1 - vx1 * t1;
                }
                else
                {
                    nowt = t2;
                    x = x2 + vx2 * t2;
                }
                vx = -vx;
            }
        };
        if (vx1 == 0 && vx2 == 0)
        {
            double s = 2.0 * (x2 - x1) / abs(vx);
            t = fmod(t, s);
        }
        cout << fixed << setprecision(9) << calc() << ' ' << y << '\n';
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
