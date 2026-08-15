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
    int a, b, n, s;
    Main()
    {
        cin >> a >> b >> n >> s;
        if (s % a || (i64)a * n < s)
        {
            cout << "YES\n";
            for (int i = 0; i < n; ++i)
                cout << a << ' ';
            cout << '\n';
            return;
        }
        if (s % b || (i64)b * n < s)
        {
            cout << "YES\n";
            for (int i = 0; i < n; ++i)
                cout << b << ' ';
            cout << '\n';
            return;
        }
        int g = __gcd(a, b);
        s /= g, a /= g, b /= g;
        if (a > b)
            swap(a, b);
        if (b > 2 && s != b && s != a)
        {
            cout << "YES\n";
            int c = s / b;
            for (int i = 0; i < n; ++i)
            {
                if (i % c == 0)
                    cout << a * g << ' ';
                else
                    cout << b * g << ' ';
            }
            return;
        }
        cout << "NO\n";
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
