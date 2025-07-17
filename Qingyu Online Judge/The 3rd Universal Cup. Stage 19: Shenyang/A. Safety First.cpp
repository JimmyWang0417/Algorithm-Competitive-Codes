#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2005;
constexpr int M = 47;
constexpr int mod = 998244353;
typedef long long ll;
int _f[2][M][N], _g[2][M][N];
ll answer[N][N];
inline void init()
{
	int n = 2000, m = 2000;
	int block = 45, num = m / block;
	auto f = _f[0], lasf = _f[1];
	auto g = _g[0], lasg = _g[1];
	f[1][1] = 1;
	for (int i = 1; i <= block; ++i)
		g[i][i] = 1;
	for (int i = 1; i <= n; ++i)
	{
		swap(f, lasf);
		swap(g, lasg);
		memset(f, 0, sizeof(_f[0]));
		memset(g, 0, sizeof(_g[0]));
		
		for (int j = 1; j <= block; ++j)
			for (int k = 0; k <= m; ++k)
			{
				(f[j][k] += lasf[j][k]) %= mod;
				(f[j + 1][k + 1] += lasf[j][k]) %= mod;
				if (j + k <= m) 
					(lasf[j][j + k] += lasf[j][k]) %= mod;
				if (j * block + k <= m) 
					(lasg[block][j * block + k] += lasf[j][k]) %= mod;
			}
		for (int j = block; j >= 1; --j)
			for (int k = 0; k <= m; ++k)
			{
				(g[j][k] += lasg[j][k]) %= mod;
				if (j + k <= m)
					(g[j][j + k] += lasg[j][k]) %= mod;
				(lasg[j - 1][k] += lasg[j][k]) %= mod;
			}
		for (int j = 1; j <= m; ++j)
			answer[i][j] = lasg[0][j];
	}
}
inline void _main()
{
	int n, m;
	cin >> n >> m;
	cout << answer[n][m] << '\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	init();
	int test = 1;
	cin >> test;
	while (test--)
		_main();
	return 0;
}