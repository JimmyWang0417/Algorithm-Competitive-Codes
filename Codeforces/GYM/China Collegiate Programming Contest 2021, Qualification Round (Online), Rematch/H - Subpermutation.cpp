#include <bits/stdc++.h>
#define int long long
#define N 1000005
#define mo 1000000007
using namespace std;
inline int read()
{
    int x = 0, f = 1;
    char c = getchar();
    while (c < 48)
    {
        if (c == '-')
            f = 0;
        c = getchar();
    }
    while (c >= 48)
        x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    return f ? x : -x;
}
int n, m;
int f[N], inv[N], finv[N], pre[N];
void init()
{
    f[0] = f[1] = inv[1] = finv[0] = finv[1] = pre[1] = 1;
    for (int i = 2; i < N; i++)
    {
        f[i] = f[i - 1] * i % mo;
        inv[i] = mo - (mo / i) * inv[mo % i] % mo;
        finv[i] = finv[i - 1] * inv[i] % mo;
        pre[i] = (pre[i - 1] + finv[i]) % mo;
    }
}
void solve()
{
    n = read();
    m = read();
    int res = (f[n - m + 1] * f[m] % mo + (m - 1) * f[m] % mo * f[n - m] % mo - f[m] * pre[m - 1] % mo + mo) % mo;
    cout << res << endl;
}
signed main()
{
    int T = read();
    init();
    while (T--)
        solve();
    return 0;
}