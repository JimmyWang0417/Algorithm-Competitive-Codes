#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e3 + 5;
typedef long long ll;
int n, m, p;
double dp[N][N];
inline void _main()
{
	cin >> n >> m >> p;
	for (int i = n; i >= 1; --i)
		for (int j = m; j >= 1; --j)
		{
			if (i == n && j == m)
				continue;
			if (i == n)
				dp[i][j] = dp[i][j + 1] + p / 4.0;
			else if (j == m)
				dp[i][j] = dp[i + 1][j] + p / 4.0;
			else
			{
				double a = min(dp[i + 1][j], dp[i][j + 1]);
				double b = max(dp[i + 1][j], dp[i][j + 1]);
				if (b - a >= p)
					dp[i][j] = a + p / 4.0;
				else
					dp[i][j] = 0.5 * a + 0.5 * ((p - b + a) / p * b + (b - a) / p * (0.5 * (b - a) + a));
			}
		}
	printf("%.8lf\n", dp[1][1]);
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