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
    vector<int> a;
    Main()
    {
        cin >> n;
        a.resize(n);
        for (int &i : a)
            cin >> i;
        ranges::sort(a);
        int L = -1, R = -1;
        for (int l = 0; l + 2 < n; ++l)
        {
            int r = (int)(ranges::lower_bound(a, a[l] + a[l + 1]) - a.begin() - 1);
            if (r - l + 1 >= 3 && r - l > R - L)
            {
                L = l;
                R = r;
            }
        }
        if (L == -1)
            cout << 0 << '\n';
        else
        {
            cout << R - L + 1;
            for (int i = L; i <= R; ++i)
                cout << ' ' << a[i];
            cout << '\n';
        }
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1, _T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
