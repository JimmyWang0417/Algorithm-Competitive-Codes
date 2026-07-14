#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
struct Main
{
    int m, d1, n, d2, k;
    constexpr static int month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    Main()
    {
        cin >> m >> d1 >> n >> d2 >> k;
        if (tie(m, d1) > tie(n, d2))
        {
            swap(m, n);
            swap(d1, d2);
        }
        bool exist = false;
        for (int y = 2025; y < 2025 + k; ++y)
        {
            auto calc = [&](int f)
            {
                if (f == 2)
                {
                    if (y % 100 == 0)
                    {
                        if (y % 400 == 0)
                            return month[2] + 1;
                    }
                    else if (y % 4 == 0)
                        return month[2] + 1;
                }
                return month[f];
            };
            {
                int d = 0;
                for (int i = m; i < n; ++i)
                    d += calc(i);
                d += min(d2, calc(n)) - min(d1, calc(m));
                if (d % 7 == 0)
                {
                    cout << y << '\n';
                    exist = true;
                }
            }
        }
        if (!exist)
            cout << "No Answer\n";
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