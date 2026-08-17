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
struct Main
{
    int L, W, H;
    int p, q, r;
    struct node
    {
        int x, y, z;
        int f, g, h;
    };
    int n;
    vector<node> a;
    Main()
    {
        cin >> L >> W >> H;
        cin >> p >> q >> r;
        cin >> n;
        a.resize(n);
        for (auto &[x, y, z, f, g, h] : a)
            cin >> x >> y >> z;
        if (n % ((i64)(p + 1) * (q + 1) * (r + 1)))
        {
            cout << 0 << '\n';
            return;
        }
        i64 res = 1;

        sort(a.begin(), a.end(), [](auto x, auto y) { return x.x < y.x; });
        for (int i = 0, j; j = i + n / (p + 1), i < n; i = j)
        {
            for (int k = i; k < j; ++k)
                a[k].f = i / (n / (p + 1));
            if (j < n)
                (res *= a[j].x - a[j - 1].x) %= mod;
        }

        sort(a.begin(), a.end(), [](auto x, auto y) { return x.y < y.y; });
        for (int i = 0, j; j = i + n / (q + 1), i < n; i = j)
        {
            for (int k = i; k < j; ++k)
                a[k].g = i / (n / (q + 1));
            if (j < n)
                (res *= a[j].y - a[j - 1].y) %= mod;
        }

        sort(a.begin(), a.end(), [](auto x, auto y) { return x.z < y.z; });
        for (int i = 0, j; j = i + n / (r + 1), i < n; i = j)
        {
            for (int k = i; k < j; ++k)
                a[k].h = i / (n / (r + 1));
            if (j < n)
                (res *= a[j].z - a[j - 1].z) %= mod;
        }

        auto ck = n / ((p + 1) * (q + 1) * (r + 1));
        map<tuple<int, int, int>, int> mp;
        for (int i = 0; i < n; ++i)
            mp[{a[i].f, a[i].g, a[i].h}]++;
        for (auto [_, x] : mp)
        {
            if (x != ck)
            {
                cout << 0 << '\n';
                return;
            }
        }
        cout << res << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int test = 1;
    // cin >> test;
    while (test--)
        Main();
    return 0;
}

