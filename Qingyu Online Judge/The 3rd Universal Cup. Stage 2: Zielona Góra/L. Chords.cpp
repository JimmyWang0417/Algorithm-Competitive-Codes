#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 2e5 + 5;
int n, a[N];
vector<int> dp[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		int u, v;
		cin >> u >> v;
		a[v] = u;
	}
	for (int i = 1; i <= 2 * n; ++i)
	{
		dp[i] = dp[i - 1];
		if (!a[i])
			continue;
		int j = 0;
		for (int k = (int)dp[i].size() - 1; k >= 0; --k)
		{
			if (dp[i][k] > a[i])
			{
				j = k + 1;
				break;
			}
		}
		if ((int)dp[i].size() == j)
			dp[i].push_back(0);
		dp[i][j] = max(dp[i][j], a[i]);
		for (int k = 0; k < (int)dp[a[i] - 1].size(); ++k)
		{
			if (k + j + 1 == dp[i].size())
				dp[i].push_back(0);
			dp[i][k + j + 1] = max(dp[i][k + j + 1], dp[a[i] - 1][k]);
		}
	}
	cout << dp[2 * n].size() << '\n';
	return 0;
}