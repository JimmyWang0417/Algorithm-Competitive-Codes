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
    Main()
    {
        u64 a, b;
        cin >> a >> b;
        if (b == 1)
        {
            cout << "0\n";
            return;
        }
        if (a % 2 != b % 2)
        {
            cout << "broken message\n";
            return;
        }
        if (a % 2 == 0)
        {
            u64 res = 1;
            for (int i = 0; i <= 64; ++i)
            {
                if (res == b)
                {
                    cout << i << '\n';
                    return;
                }
                res *= a;
            }
        }
        u64 k = 1, c = (a % 2 == 0 ? 1 : 0), d = (a % 2 == 0 ? a : 1), e = a;
        for (int i = 1; i < 64; ++i)
        {
            auto calc = [&](u64 x, int y)
            {
                if (y == 64)
                    return x;
                return x & (((u64)1 << y) - 1);
            };
            bool left = (calc(d, i + 1) == calc(b, i + 1));
            bool right = (calc(d * e, i + 1) == calc(b, i + 1));
            if (left && right)
            {
            }
            else if (!left && !right)
            {
                cout << "broken message\n";
                return;
            }
            else
            {
                if (right)
                {
                    c += k;
                    d *= e;
                }
                k *= 2;
                e *= e;
            }
        }
        cout << c << '\n';
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
