#include <bits/stdc++.h>
using namespace std;
constexpr int N = 50 * 100000 + 5;
int n, a[N], b[N];
int buf[2][N];
inline void _main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i] >> b[i];
	auto f = buf[0], g = buf[1];
	memset(f, 0x3f, sizeof(buf[0]));
	f[0] = 0;
	for (int i = 1; i <= n; ++i)
	{
		swap(f, g);
		memset(f, 0x3f, sizeof(buf[0]));
		for (int j = 0; j <= N - 5; ++j)
		{
			f[j] = g[j] + b[i];
			if (j >= a[i])
				f[j] = min(f[j], g[j - a[i]]);
		}
	}
	int ans = INT_MAX;
	for (int j = 0; j <= N - 5; ++j)
		ans = min(ans, max(j, f[j]));
	cout << ans << '\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int test = 1;
//	cin >> test; 
	while (test--)
		_main();
	return 0;
}