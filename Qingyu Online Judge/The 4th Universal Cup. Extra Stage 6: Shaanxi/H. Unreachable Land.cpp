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
vector<int> power;
auto init(int n)
{
    power.resize(n + 1);
    power[0] = 1;
    for (int i = 1; i <= n; ++i)
        power[i] = power[i - 1] * 2 % mod;
}
struct Main
{
    int a, b, m;
    vector<int> dp;
    vector<vector<int>> tagA, tagB;
    Main()
    {
        cin >> a >> b >> m;
        int block = (int)sqrt(a);
        dp.resize(a + 5);
        dp[b] = 1;
        for (int k = 1; k <= min(block, m); ++k)
            for (int i = 0; i < k; ++i)
                for (int j = i + k; j <= a; j += k)
                    (dp[j] += (int)((i64)dp[i] * power[k - i - 1] % mod)) %= mod;
        auto maxC = a / (block + 1);
        tagA.resize(maxC + 1, vector<int>(a + 5));
        tagB.resize(maxC + 1, vector<int>(a + 5));
        for (int i = 0; i <= a; ++i)
        {
            for (int c = 1; c <= maxC; ++c)
            {
                tagA[c][i % c] = (2 * tagA[c][i % c] % mod + tagB[c][i]) % mod;
                (dp[i] += tagA[c][i % c]) %= mod;
            }
            for (int c = 1; c <= maxC; ++c)
            {
                int l = max(i + 1, block + 1);
                int r = min(m, (a - i) / c);
                if (l > r)
                    break;
                (tagB[c][l * c + i] += (int)((i64)dp[i] * power[l - i - 1] % mod)) %= mod;
                if ((r + 1) * c + i <= a)
                    (tagB[c][(r + 1) * c + i] -= (int)((i64)dp[i] * power[(r + 1) - i - 1] % mod)) %= mod;
            }
        }
        // for (int i = 0; i <= a; ++i)
        //     cout << (dp[i] + mod) % mod << ' ';
        // cout << '\n';
        cout << (dp[a] + mod) % mod << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init(2e5);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}