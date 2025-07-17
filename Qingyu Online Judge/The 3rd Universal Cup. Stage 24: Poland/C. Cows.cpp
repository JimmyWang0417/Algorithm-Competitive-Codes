#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
constexpr int N = 2e5 + 5;
int n, h[N];
int a[N], b[N];
inline bool check(int mid)
{
    for (int i = 1; i <= n; ++i)
    {
        a[i] = mid;
        b[i] = h[i];
    }
    auto update = [](int &x, int l, int r)
    {
        if (x <= l)
            return;
        int y = x - l;
        if (y >= (r - l) * 2)
            x -= r - l;
        else
            x = (y + 1) / 2 + l; 
    };
    for (int i = 1; i < n; ++i)
    {
        if (a[i] < 0)
            return false;
        if (a[i] >= b[i])
        {
            update(b[i + 1], b[i], a[i]);
            if (i > 1 && a[i - 1] > a[i])
                update(b[i + 1], a[i - 1], mid);
        }
        else
            a[i + 1] = a[i] * 2 - b[i];
    }
    return a[n] >= b[n];
}
inline void _main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> h[i];
    int l = *min_element(h + 1, h + 1 + n), r = *max_element(h + 1, h + 1 + n);
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid))
            r = mid - 1;
        else
            l = mid + 1;
    }
    cout << l << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _main();
    return 0;
}