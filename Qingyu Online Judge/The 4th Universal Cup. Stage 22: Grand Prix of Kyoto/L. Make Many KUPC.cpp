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
    string s;
    Main()
    {
        cin >> n >> s;
        queue<i64> A, B, C;
        i64 ans = 0;
        for (int i = n; i >= 1; --i)
        {
            if (s[i - 1] == 'C')
                A.push(i);
            else if (s[i - 1] == 'P')
            {
                if (!A.empty())
                {
                    B.push(A.front() * i % mod);
                    A.pop();
                }
            }
            else if (s[i - 1] == 'U')
            {
                if (!B.empty())
                {
                    C.push(B.front() * i % mod);
                    B.pop();
                }
            }
            else if (s[i - 1] == 'K')
            {
                if (!C.empty())
                {
                    (ans += C.front() * i) %= mod;
                    C.pop();
                }
            }
        }
        cout << ans << '\n';
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
