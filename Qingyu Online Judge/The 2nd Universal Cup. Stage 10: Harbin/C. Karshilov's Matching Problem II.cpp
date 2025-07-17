#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1.5e5 + 5;
int n, m;
int w[N];
char S[N], T[N];
int z[N], t[N], p[N];
inline void exkmp()
{
	z[1] = n;
	for (int i = 2, l = 0, r = 0; i <= n; ++i)
	{
		z[i] = max(0, min(z[i - l + 1], r - i + 1));
		while (i + z[i] <= n && S[1 + z[i]] == S[i + z[i]])
			++z[i];
		if (i + z[i] - 1 > r)
		{
			l = i;
			r = i + z[i] - 1;
		}
	}
	for (int i = 1, l = 0, r = 0; i <= n; ++i)
	{
		t[i] = max(0, min(z[i - l + 1], r - i + 1));
		while (i + t[i] <= n && S[1 + t[i]] == T[i + t[i]])
			++t[i];
		if (i + t[i] - 1 > r)
		{
			l = i;
			r = i + t[i] - 1;
		}
	}
}
inline void kmp()
{
	for (int i = 2, j = 0; i <= n; ++i)
	{
		while (j && S[j + 1] != S[i])
			j = p[j];
		if (S[j + 1] == S[i])
			++j;
		p[i] = j;
	}
}
ll pre[N], sum[N], sumw[N];
int Log[N], dp[23][N];
inline void init()
{
	exkmp();
	kmp();
	
	for (int i = 1; i <= n; ++i)
		sumw[i] = sumw[i - 1] + w[i];
	for (int i = 1; i <= n; ++i)
		pre[i] = pre[i - 1] + sumw[t[i]];
		
	for (int i = 1; i <= n; ++i)
		sum[i] = sum[p[i]] + w[i];
	for (int i = 2; i <= n; ++i)
		sum[i] += sum[i - 1];
		
	Log[0] = -1;
	for (int i = 1; i <= n; ++i)
		Log[i] = Log[i >> 1] + 1;
	for (int i = 1; i <= n; ++i)
		dp[0][i] = i + t[i] - 1;
	for (int j = 0; j < Log[n]; ++j)
		for (int i = 1; i + (2 << j) - 1 <= n; ++i)
			dp[j + 1][i] = max(dp[j][i], dp[j][i + (1 << j)]);
}
inline int query(int x, int y)
{
	int k = Log[y - x + 1];
	return max(dp[k][x], dp[k][y - (1 << k) + 1]);
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m >> (S + 1) >> (T + 1);
	for (int i = 1; i <= n; ++i)
		cin >> w[i];
	init();
	for (int i = 1; i <= m; ++i)
	{
		int x, y;
		cin >> x >> y;
		int l = x, r = y;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			if (query(x, mid) > y)
				r = mid - 1;
			else
				l = mid + 1;
		}
		cout << pre[l - 1] - pre[x - 1] + sum[y - l + 1] << '\n';
	}
	return 0;
}