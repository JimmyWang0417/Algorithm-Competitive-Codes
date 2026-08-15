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
    int n, m, k;
    vector<pair<int, int>> a, b;
    auto checka(i64 mid)
    {
        i64 now = mid - k;
        for (int i = n; i >= 1; --i, now -= 2 * k)
            if (a[i].first > now)
                return false;
        now = mid - 2 * k;
        for (int i = m; i >= 1; --i, now -= 2 * k)
            if (b[i].first > now)
                return false;
        return true;
    }
    auto checkb(i64 mid)
    {
        i64 now = mid - k;
        for (int i = m; i >= 1; --i, now -= 2 * k)
            if (b[i].first > now)
                return false;
        now = mid - 2 * k;
        for (int i = n; i >= 1; --i, now -= 2 * k)
            if (a[i].first > now)
                return false;
        return true;
    }
    Main()
    {
        cin >> n >> m >> k;
        a.resize(n + 5), b.resize(m + 5);
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i].first;
            a[i].second = i;
        }
        for (int i = 1; i <= m; ++i)
        {
            cin >> b[i].first;
            b[i].second = i;
        }
        sort(a.begin() + 1, a.begin() + 1 + n);
        sort(b.begin() + 1, b.begin() + 1 + m);
        i64 l = 0, r = 1e18;
        while (l <= r)
        {
            auto mid = (l + r) / 2;
            if (checka(mid) || checkb(mid))
                r = mid - 1;
            else
                l = mid + 1;
        }
        vector<tuple<i64, int, int>> p;
        if (checka(l))
        {
            i64 now = l - k;
            for (int i = n; i >= 1; --i, now -= 2 * k)
                p.emplace_back(now, 0, a[i].second);
            now = l - 2 * k;
            for (int i = m; i >= 1; --i, now -= 2 * k)
                p.emplace_back(now, 1, b[i].second);
        }
        else
        {
            i64 now = l - k;
            for (int i = m; i >= 1; --i, now -= 2 * k)
                p.emplace_back(now, 1, b[i].second);
            now = l - 2 * k;
            for (int i = n; i >= 1; --i, now -= 2 * k)
                p.emplace_back(now, 0, a[i].second);
        }
        cout << l << '\n';
        sort(p.begin(), p.end());
        for (auto [x, y, z] : p)
            cout << x << ' ' << y << ' ' << z << '\n';
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
