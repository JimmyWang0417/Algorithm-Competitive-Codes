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
constexpr double eps = 1e-7;
struct Main
{
    Main()
    {
        int n;
        cin >> n;
        int maxx = 0, g = 0;
        for (int i = 0; i < n; ++i)
        {
            int x;
            cin >> x;
            maxx = max(maxx, x);
            g = __gcd(g, x);
        }
        cout << ((maxx / g - n) % 3 == 0 ? "YES\n" : "NO\n");
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

