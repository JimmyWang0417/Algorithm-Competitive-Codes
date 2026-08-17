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
constexpr int K = 2000;
struct Main
{
    int a, b;
    Main()
    {
        cin >> a >> b;
        vector<double> f(a + b + 1), g(a + b + 1);
        for (int i = 1, lasL = 1, lasR = 0; i <= a + b; ++i)
        {
            int mid = (int)((double)i * a / (a + b));
            int L = max(0, mid - K), R = min(mid + K, i);
            for (int j = L; j <= R; ++j)
                f[j] = max((double)0, (2 * j - i + (j > 0 ? j * g[j - 1] : 0) + (i - j) * g[j]) / i);
            for (int j = lasL; j <= lasR; ++j)
                g[j] = 0;
            lasL = L, lasR = R;
            swap(f, g);
        }
        cout << fixed << setprecision(9) << g[a] << '\n';
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

