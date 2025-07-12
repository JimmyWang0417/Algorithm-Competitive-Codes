#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
constexpr int N = 2005;
constexpr int mod = 1e9 + 7;
constexpr int inv2 = (mod + 1) / 2;
int n, m;
int C[N][N];
int a[N];
inline void _main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    sort(a + 1, a + 1 + n);
    ll sum1 = 0, sum2 = 0;
    for (int i = 1; i <= m; ++i)
        sum1 += a[i];
    for (int i = n - m + 1; i <= n; ++i)
        sum2 += a[i];
    if (a[m] == a[n - m + 1])
    {
        int cnt1 = 0, cnt2 = 0, cnt = 0;
        for (int i = 1; i <= n; ++i)
            cnt += (a[i] == a[m]);
        for (int i = 1; i <= m; ++i)
            cnt1 += (a[i] == a[m]);
        for (int i = n - m + 1; i <= n; ++i)
            cnt2 += (a[i] == a[n - m + 1]);
        cout << sum2 - sum1 << ' ' << (ll)C[cnt][cnt1] * C[cnt - cnt1][cnt2] % mod * (a[1] == a[n] ? inv2 : 1) % mod << '\n';
    }
    else
    {
        int cnt1 = 0, cnt2 = 0, cnt = 0, cnt0 = 0;
        for (int i = 1; i <= n; ++i)
        {
            cnt += (a[i] == a[m]);
            cnt0 += (a[i] == a[n - m + 1]);
        }
        for (int i = 1; i <= m; ++i)
            cnt1 += (a[i] == a[m]);
        for (int i = n - m + 1; i <= n; ++i)
            cnt2 += (a[i] == a[n - m + 1]);
        cout << sum2 - sum1 << ' ' << (ll)C[cnt][cnt1] * C[cnt0][cnt2] % mod << '\n';
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    for (int i = C[0][0] = 1; i <= 2000; ++i)
        for (int j = C[i][0] = 1; j <= 2000; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    int T = 1;
    // cin >> T;
    while (T--)
        _main();
    return 0;
}