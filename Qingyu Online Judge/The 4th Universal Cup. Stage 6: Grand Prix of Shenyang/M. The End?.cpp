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
    array<int, 8> a, b;
    auto calc(const vector<int> &p)
    {
        double res = 0;
        for (int S = 0; S < (1 << 7); ++S)
        {
            double times = 1;
            vector<int> x = p, y, z;
            for (int i = 0; i < 4; ++i)
            {
                int X = a[x[i * 2]], Y = b[x[i * 2 + 1]];
                if ((S >> i) & 1)
                {
                    times *= (double)X / (X + Y);
                    y.push_back(x[i * 2]);
                }
                else
                {
                    times *= (double)Y / (X + Y);
                    y.push_back(x[i * 2 + 1]);
                }
            }
            for (int i = 0; i < 2; ++i)
            {
                int X = a[y[i * 2]], Y = b[y[i * 2 + 1]];
                if ((S >> (i + 4)) & 1)
                {
                    times *= (double)X / (X + Y);
                    z.push_back(y[i * 2]);
                }
                else
                {
                    times *= (double)Y / (X + Y);
                    z.push_back(y[i * 2 + 1]);
                }
            }
            {
                int c;
                int X = a[z[0]], Y = b[z[1]];
                if ((S >> 6) & 1)
                {
                    times *= (double)X / (X + Y);
                    c = z[0];
                }
                else
                {
                    times *= (double)Y / (X + Y);
                    c = z[1];
                }
                if (c == 0)
                    res += times;
            }
        }
        return res;
    }
    Main()
    {
        vector p({0, 1, 2, 3, 4, 5, 6, 7});
        for (int i = 0; i < 8; ++i)
            cin >> a[i] >> b[i];
        double ans = 0;
        do
        {
            ans = max(ans, calc(p));
        } while (next_permutation(p.begin(), p.end()));
        cout << fixed << setprecision(9) << ans << '\n';
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
