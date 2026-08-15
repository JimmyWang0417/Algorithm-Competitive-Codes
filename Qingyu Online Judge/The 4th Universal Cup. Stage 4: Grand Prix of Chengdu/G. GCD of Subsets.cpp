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
        i64 n, m, k;
        cin >> n >> k >> m;
        auto a = n / k, b = min(m, n - a);
        if (a % 2 == 1)
        {
            auto res = (a + 1) / 2 + b;
            res += (m - b) / 2;
            cout << res << '\n';
        }
        else
        {
            auto res = a / 2 + b;
            if (m - b)
                res += (m - b - 1) / 2 + 1;
            cout << res << '\n';
        }
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
