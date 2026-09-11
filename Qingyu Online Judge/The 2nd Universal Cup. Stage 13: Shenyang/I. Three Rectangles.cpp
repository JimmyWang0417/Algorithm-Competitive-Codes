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
    int H, W;
    array<pair<int, int>, 3> a;
    auto check1()
    {
        for (auto i : a)
            if (i == make_pair(H, W))
                return true;
        return false;
    }
    Main()
    {
        cin >> H >> W;
        for (auto &[x, y] : a)
            cin >> x >> y;
        if (check1())
        {
            i64 res = 1;
            for (auto [x, y] : a)
                (res *= (i64)(H - x + 1) * (W - y + 1) % mod) %= mod;
            cout << res << '\n';
            return;
        }
        i64 res = 0;
        { // 2 hori
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                    if (i == j)
                        continue;
                    const int k = 3 ^ i ^ j;
                    if (H == a[i].first && H == a[j].first && a[i].second + a[j].second >= W)
                        (res += (i64)(H - a[k].first + 1) * (W - a[k].second + 1)) %= mod;
                }
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                    const int k = 3 ^ i ^ j;
                    if (i == j || j > k)
                        continue;
                    if (H == a[i].first && H == a[j].first && H == a[k].first &&
                        a[i].second + a[j].second >= W && a[i].second + a[k].second >= W)
                            (res -= 2) %= mod;
                }
        }
        { // 2 vertigo
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                    if (i == j)
                        continue;
                    const int k = 3 ^ i ^ j;
                    if (W == a[i].second && W == a[j].second && a[i].first + a[j].first >= H)
                        (res += (i64)(H - a[k].first + 1) * (W - a[k].second + 1)) %= mod;
                }
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                    const int k = 3 ^ i ^ j;
                    if (i == j || j > k)
                        continue;
                    if (W == a[i].second && W == a[j].second && W == a[k].second &&
                        a[i].first + a[j].first >= H && a[i].first + a[k].first >= H)
                            (res -= 2) %= mod;
                }
        }
        { // 3 hori
            if (H == a[0].first && H == a[1].first && H == a[2].first)
                for (int i = 0; i < 3; ++i)
                    for (int j = 0; j < 3; ++j)
                    {
                        if (i == j)
                            continue;
                        const int k = 3 ^ i ^ j;
                        if (a[i].second + a[j].second < W)
                            (res += max(min(W - a[k].second - 1, a[i].second) - max(1, W - a[j].second - a[k].second) + 1, 0)) %= mod;
                    }
        }
        { // 3 verti
            if (W == a[0].second && W == a[1].second && W == a[2].second)
                for (int i = 0; i < 3; ++i)
                    for (int j = 0; j < 3; ++j)
                    {
                        if (i == j)
                            continue;
                        const int k = 3 ^ i ^ j;
                        if (a[i].first + a[j].first < H)
                            (res += max(min(H - a[k].first - 1, a[i].first) - max(1, H - a[j].first - a[k].first) + 1, 0)) %= mod;
                    }
        }
        { // 3 cross hori
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                    if (i == j)
                        continue;
                    const int k = 3 ^ i ^ j;
                    if (a[i].second == W && a[j].second == W)
                        continue;
                    if (a[i].first == H || a[j].first == H)
                        continue;
                    if (a[k].first == H && a[i].first + a[j].first >= H &&
                        a[k].second + min(a[i].second, a[j].second) >= W)
                        (res += 2) %= mod;
                }
        }
        { // 3 cross verti
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                {
                    if (i == j)
                        continue;
                    const int k = 3 ^ i ^ j;
                    if (a[i].first == H || a[j].first == H)
                        continue;
                    if (a[i].second == W || a[j].second == W)
                        continue;
                    if (a[k].second == W && a[i].second + a[j].second >= W &&
                        a[k].first + min(a[i].first, a[j].first) >= H)
                        (res += 2) %= mod;
                }
        }
        cout << (res + mod) % mod << '\n';
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