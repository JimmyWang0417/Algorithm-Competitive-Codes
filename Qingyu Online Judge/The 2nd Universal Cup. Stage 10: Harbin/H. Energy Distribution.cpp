#include <bits/stdc++.h>
using namespace std;
constexpr int N = 15;
constexpr double eps = 1e-6;
int n, a[N][N];
double g[N][N];
inline bool gause()
{
	for (int i = 0; i < n; ++i)
	{
		int where = -1;
		for (int j = i; j <= n; ++j)
			if (abs(g[j][i]) > eps)
			{
				where = i;
				break;
			}
		if (where == -1)
			return false;
		if (where != i)
			swap(g[where], g[i]);
		for (int j = i + 1; j < n; ++j)
		{
			double d = g[j][i] / g[i][i];
			for (int k = i; k <= n; ++k)
				g[j][k] -= g[i][k] * d;
		}
	}
	for (int i = n - 1; i >= 0; --i)
	{
		for (int j = i + 1; j < n; ++j)
			g[i][n] -= g[i][j] * g[j][n];
		g[i][n] /= g[i][i];
		if (g[i][n] < 0)
			return false;
	}
//	printf("ans:\n");
//	for (int i = 0; i < n; ++i)
//		printf("%lf ", g[i][n]);
//	putchar('\n');
	return true;
}
inline double calc()
{
	double ans = 0;
	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
			ans += g[i][n] * g[j][n] * a[i][j];
	return ans;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cin >> a[i][j];
	double res = 0;
	for (int S = 0; S < (1 << n); ++S)
	{
		int fir = -1, nxt = -1;
		for (int i = 0; i < n; ++i)
		{
			if ((S >> i) & 1)
				continue;
			if (fir == -1)
				fir = i;
			else if (nxt == -1)
			{
				nxt = i;
				break;
			}
		}
		if (nxt == -1)
			continue;
		for (int i = 0; i < n; ++i)
			if ((S >> i) & 1)
			{
				g[i][i] = 1;
				g[i][n] = 0;
			}
			else
			{
				int x = (i == fir) ? nxt : fir;
				for (int j = 0; j < n; ++j)
				{
					if (j == x)
						continue;
					g[i][j] = a[i][j] - a[x][j] - a[i][x];
				}
				g[i][i] = -2 * a[i][x];
				g[i][n] = -a[i][x];
			}
//		printf("%d:\n", S);
		if (gause())
			res = max(res, calc());
		memset(g, 0, sizeof(g));
	}
	printf("%.9lf\n", res);
	return 0;
}