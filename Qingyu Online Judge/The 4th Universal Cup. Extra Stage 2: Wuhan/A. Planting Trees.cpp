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
    template <typename T>
    auto euclid(T a, T b, T c, T n)
    {
        if (a == 0 && b >= 0)
            return b / c * (n + 1);
        else if (0 <= a && a < c && 0 <= b && b < c)
        {
            T m = (a * n + b) / c;
            return n * m - euclid(c, c - b - 1, a, m - 1);
        }
        else
        {
            T ac = a >= 0 ? a / c : (a + 1) / c - 1;
            T bc = b >= 0 ? b / c : (b + 1) / c - 1;
            return n * (n + 1) / 2 * ac + (n + 1) * bc + euclid(a - ac * c, b - bc * c, c, n);
        }
    }
    Main()
    {
        i64 f, x, g, y, n, m;
        cin >> f >> x >> g >> y >> n >> m;
        auto res = n - euclid(g, y, m, n - 1) + euclid(f, x, m, n - 1) + euclid(g - f, y - x - 1, m, n - 1);
        cout << res << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; ++i)
        Main();
    return 0;
}
