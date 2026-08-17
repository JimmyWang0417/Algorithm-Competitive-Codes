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
        int n;
        cin >> n;
        vector<int> v(n + 1);
        v[1] = n;
        v[2] = n + 1;
        for (int i = 3; i <= n; ++i)
            v[i] = v[1] + v[i - 1] + 1;
        cout << n << '\n';
        for (int i = 1; i <= n; ++i)
            cout << i << ' ';
        cout << '\n';
        for (int i = 1; i <= n; ++i)
            cout << v[i] << ' ';
        cout << '\n';
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
