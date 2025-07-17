#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N = 505;
int n, X[N], Y[N];
int minX[N][N], minY[N][N];
ll dp[N][N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> X[i] >> Y[i];
	for (int i = 1; i <= n; ++i)
	{
		minX[i][i] = X[i];
		minY[i][i] = Y[i];
		for (int j = i + 1; j <= n; ++j)
		{
			minX[i][j] = min(minX[i][j - 1], X[j]);
			minY[i][j] = min(minY[i][j - 1], Y[j]);
		}
	}
	for (int len = 2; len <= n + 1; ++len)
	{
		for (int i = 0, j; (j = i + len - 1) <= n; ++i)
		{
			dp[i][j] = LONG_LONG_MAX;
			for (int k = i; k < j; ++k)
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] 
										+ minX[i][k] + minX[k + 1][j] - 2 * minX[i][j]
										+ minY[i][k] + minY[k + 1][j] - 2 * minY[i][j]);
		}
	}
	cout << dp[0][n] << '\n';
	return 0;
}