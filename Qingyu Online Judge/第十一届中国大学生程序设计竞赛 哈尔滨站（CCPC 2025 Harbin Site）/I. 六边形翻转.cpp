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
    int n, m;
    Main()
    {
        cin >> n >> m;
        map<int, int> X, Y, Z;
        for (int i = 0; i < n; ++i)
        {
            int x, y, z;
            cin >> x >> y >> z;
            ++X[x], ++Y[y], ++Z[z];
        }
        for (int i = 0; i < m; ++i)
        {
            int x, y, z;
            cin >> x >> y >> z;
            ++X[x], ++Y[y], ++Z[z];
        }
        for (auto [_, y] : X)
            if (y & 1)
            {
                cout << "NO\n";
                return;
            }
        for (auto [_, y] : Y)
            if (y & 1)
            {
                cout << "NO\n";
                return;
            }
        for (auto [_, y] : Z)
            if (y & 1)
            {
                cout << "NO\n";
                return;
            }
        cout << "YES\n";
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
