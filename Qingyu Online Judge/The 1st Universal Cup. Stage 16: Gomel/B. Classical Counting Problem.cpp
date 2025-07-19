#include <bits/stdc++.h>
using namespace std;
constexpr int N = 105;
constexpr int M = 1e4 + 5;
constexpr int mod = 998244353;
template <typename T>
inline void add(T &x, T y)
{
	x += y;
	if (x >= mod)
		x -= mod;
}
template <typename T>
inline void del(T &x, T y)
{
	x -= y;
	if (x < 0)
		x += mod;
}
int n, m, v, a[N];
int _buf[2][M];
inline void work()
{
	cin >> n >> m >> v;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	sort(a + 1, a + 1 + n);
    int ans = 0;
    for (int _minS = 1; _minS <= n; ++_minS)
    {
        int minS = a[_minS];
		auto f = _buf[0], g = _buf[1];
        f[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            swap(f, g);
            if (i >= _minS)
            {
                for (int j = 0; j <= m * v; ++j)
                	add(f[min(j + m, m * v)], g[j]);
            }
            if (i != _minS && a[i] - minS <= m)
            {
                int c = min(minS + m - a[i], m);
                for (int j = 0; j <= m * v; ++j)
                	add(f[min(j + c, m * v)], g[j]);
            }
            for (int j = 0; j <= m * v; ++j)
                g[j] = 0;
        }
        add(ans, f[m * v]);
        for (int j = 0; j <= m * v; ++j)
            f[j] = 0;
        f[0] = 1;
        for (int i = 1; i <= n; ++i)
        {
            swap(f, g);
            if (i >= _minS)
            {
                for (int j = 1; j <= n; ++j)
                	add(f[j], g[j - 1]);
            }
            if (i != _minS && a[i] - minS <= m)
            {
                for (int j = 0; j <= n; ++j)
                	add(f[j], g[j]);
            }
            for (int j = 0; j <= n; ++j)
                g[j] = 0;
        }
        for (int j = v; j <= n; ++j)
        	del(ans, f[j]);
        for (int j = 0; j <= n; ++j)
            f[j] = 0;
    }
    reverse(a + 1, a + 1 + n);
    for (int _maxT = 1; _maxT <= n; ++_maxT)
    {
        int maxT = a[_maxT];
        auto *dp = _buf[0];
        dp[0] = 1;
        for (int i = _maxT + 1; i <= n; ++i)
        {
            if (maxT - a[i] > m)
                break;
            int dec = maxT - a[i];
            for (int j = m * v; j >= dec; --j)
            	add(dp[j], dp[j - dec]);
        }
        for (int i = 0; i <= m * v; ++i)
        {
        	add(ans, dp[i]);
            dp[i] = 0;
        }
        dp[0] = 1;
        for (int i = _maxT + 1; i <= n; ++i)
        {
            if (maxT - a[i] > m)
                break;
            for (int j = v - _maxT; j >= 1; --j)
            	add(dp[j], dp[j - 1]);
        }
        for (int i = 0; i + _maxT - 1 < v; ++i)
        {
        	del(ans, dp[i]);
            dp[i] = 0;
        }
    }
    cout << ans + 1 << '\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T = 1;
	cin >> T;
	while (T--)
		work();
	return 0;
}