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
    int n;
    vector<i64> a;
    Main()
    {
        cin >> n;
        a.resize(n);
        for (auto &i : a)
            cin >> i;
        i64 g = 0;
        for (auto &i : a)
            g = gcd(g, i - a.front());
        if (g == 0)
            cout << "infinite\n";
        else
        {
            cout << g << ' ' << g / gcd(a.front(), g) << '\n';
        }
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
