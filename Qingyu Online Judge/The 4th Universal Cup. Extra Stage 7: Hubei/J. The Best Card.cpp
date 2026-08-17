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
    int n, m;
    vector<pair<int, int>> a;
    Main()
    {
        cin >> n >> m;
        a.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i].second;
        for (int i = 0; i < n; ++i)
            cin >> a[i].first;
        ranges::sort(a);
        vector<pair<i64, i64>> p;
        i64 res = 0;
        for (int i = 0, j = 0; i < n; i = j)
        {
            i64 r = a[i].first + a[i].second, A = a[i].second, B = 0;
            j = i + 1;
            while (j < n && r >= a[j].first)
            {
                int l = a[j].first - a[j - 1].first;
                B += l * (A + A - l + 1) / 2;
                A += a[j].second - l;
                r += a[j].second;
                ++j;
            }
            B += A * (A + 1) / 2;
            p.emplace_back(a[i].first, r);
            res += B;
        }
        vector<i64> A(p.size() + 1), B(p.size() + 1), C(p.size() + 1), D(p.size() + 1);
        for (int i = (int)p.size() - 1; i >= 0; --i)
        {
            auto x = p[i].second - p[i].first,
                 y = i == (int)p.size() - 1 ? 0 : p[i + 1].first - p[i].second;
            A[i] = A[i + 1] + x;
            B[i] = B[i + 1] + y;
            C[i] = C[i + 1] + x * B[i];
            D[i] = D[i + 1] + y * (y + 1) / 2;
        }
        i64 ans = 0;
        i64 len = 0;
        for (int i = (int)p.size() - 1, j = i; i >= 0; --i)
        {
            while (len > m)
            {
                len -= p[j].first - p[j - 1].second;
                --j;
            }
            i64 gap = B[i] - B[j];
            i64 cur = D[i] - D[j] + C[i] - C[j] - B[j] * (A[i] - A[j]);
            i64 sumSq = 2 * (D[i] - D[j]) - gap;
            cur += (gap * gap - sumSq) / 2;
            i64 x = p[j].second - p[i].first, y = m - gap;
            // cout << x << ' ' << y << '\n';
            cur += (x + 1 + x + y) * y / 2;
            // cout << i << ' ' << j << ' ' << x << ' ' << y << ' ' << cur << '\n';
            ans = max(ans, cur);
            if (i)
                len += p[i].first - p[i - 1].second;
        }
        cout << res + ans << '\n';
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
