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
    Main()
    {
        cin >> n;
        if (n >= 1 && n <= 8)
        {
            cout << "Yes\n0 ";
            for (int i = 1; i < n; i++)
                cout << i << " ";
            for (int i = 1; i <= 12 - n; i++)
                cout << "0 ";
            cout << '\n';
            return;
        }
        if (n == 11)
        {
            cout << "Yes\n";
            cout << "0 1 2 3 4 5 6 7 8 0 0 0\n";
            return;
        }
        if (n == 22)
        {
            cout << "Yes\n";
            cout << "0 1 2 3 4 5 6 7 8 0 1 0\n";
            return;
        }
        if (n == 33)
        {
            cout << "Yes\n";
            cout << "0 1 2 3 4 5 6 7 8 0 1 2\n";
            return;
        }
        cout << "No\n";
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

