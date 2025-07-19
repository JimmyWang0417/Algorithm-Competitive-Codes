#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 28;
int n, a[N];
ll sum[(1 << 23) + 5];
int dp[(1 << 23) + 5];
int Log[(1 << 23) + 5];
int p[N], tot;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int i = n - 1; i >= 1; --i)
		a[i] -= a[i - 1];
	for (int i = 0; i < n; ++i)
		if (a[i])
			p[tot++] = a[i];
	n = tot;
	for (int i = 0; i < n; ++i)
	{
		Log[1 << i] = i;
		for (int j = 0; j < (1 << i); ++j)
			sum[(1 << i) | j] = p[i] + sum[j];
	}
	int ans = n;
	for (int S = 1; S < (1 << n); ++S)
	{
		if (sum[S])
			continue;
		for (int T = (S - 1) & S; T; T = (T - 1) & S)
			dp[S] = max(dp[S], dp[S ^ T]);
		++dp[S];
		ans = min(ans, n - dp[S]);
	}
	cout << ans << '\n';
	return 0;
}