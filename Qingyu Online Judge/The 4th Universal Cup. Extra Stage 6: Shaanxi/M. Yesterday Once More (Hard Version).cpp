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
constexpr int mod = 1e9 + 7;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
    a %= mod;
    i64 res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
struct Main
{
    int n;
    Main()
    {
        cin >> n;
        string s;
        for (int i = 1; i < n; ++i)
            s.append("D");
        for (int i = 1; i < n; ++i)
            s.append("RDUR");
        s.append("D");
        for (int i = 1; i < n; ++i)
            s.append("L");
        for (int i = 0; i < n; ++i)
            s.append("DLDR");
        cout << s.size() << '\n' << s << '\n';
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

