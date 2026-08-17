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
    i64 x, y;
    string s;
    Main()
    {
        cin >> n >> x >> y;
        cin >> s;
        auto d = (x + y) / n;
        int A[3] = {}, B[3] = {};
        for (int i = 0; i < n; ++i)
            A[s[i] - '0']++;
        for (int i = 0; i < (x + y) % n; ++i)
            B[s[i] - '0']++;
        if (d)
        {
            for (int i = 0; i <= B[2]; ++i)
            {
                i64 a = A[0] * d + B[0] + (B[2] - i);
                i64 b = A[1] * d + B[1] + i;
                // cout << a << ' ' << b << ' ' << (x - a) / d + (y - b) / d << '\n';
                if (a <= x && b <= y &&
                    (x - a) % d == 0 && (y - b) % d == 0 &&
                    (x - a) / d + (y - b) / d == A[2] &&
                    (x - a) / d >= (B[2] - i) && (y - b) / d >= i)
                {
                    i64 c1 = B[2] - i, c2 = i, c3 = (x - a) / d - c1;
                    for (auto c : s)
                    {
                        if (c == '2')
                        {
                            if (c1)
                            {
                                c = '0';
                                --c1;
                            }
                            else if (c2)
                            {
                                c = '1';
                                --c2;
                            }
                            else if (c3)
                            {
                                c = '0';
                                --c3;
                            }
                            else
                                c = '1';
                        }
                        cout << c;
                    }
                    cout << '\n';
                    return;
                }
            }
        }
        else
        {
            for (int i = 0; i <= B[2]; ++i)
            {
                i64 a = A[0] * d + B[0] + (B[2] - i);
                i64 b = A[1] * d + B[1] + i;
                if (a == x && b == y)
                {
                    i64 c1 = B[2] - i, c2 = i;
                    for (auto c : s)
                    {
                        if (c == '2')
                        {
                            if (c1)
                            {
                                c = '0';
                                --c1;
                            }
                            else if (c2)
                            {
                                c = '1';
                                --c2;
                            }
                            else
                                c = '0';
                        }
                        cout << c;
                    }
                    cout << '\n';
                    return;
                }
            }
        }
        cout << "-1\n";
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

