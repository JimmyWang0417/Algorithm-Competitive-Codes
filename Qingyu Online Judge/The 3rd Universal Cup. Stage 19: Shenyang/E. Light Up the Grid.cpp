#include <bits/stdc++.h>
using namespace std;
int a0, a1, a2, a3;
int dis[16];
bool vis[16];
inline void init()
{
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	memset(dis, 0x3f, sizeof(dis));
	q.emplace(0, 0);
	while (!q.empty())
	{
		auto [d, u] = q.top(); 
		q.pop();
		if (vis[u])
			continue;
		vis[u] = true;
		for (int i = 0; i < 4; ++i)
		{
			int v = u ^ (1 << i);
			if (dis[v] > d + a0)
				q.emplace(dis[v] = d + a0, v);
		}
		for (int i = 0; i < 2; ++i)
		{
			int v = u ^ (3 << (i * 2));
			if (dis[v] > d + a1)
				q.emplace(dis[v] = d + a1, v);
		}
		for (int i = 0; i < 2; ++i)
		{
			int v = u ^ (5 << i);
			if (dis[v] > d + a2)
				q.emplace(dis[v] = d + a2, v);
		}
		int v = u ^ 15;
		if (dis[v] > d + a3)
			q.emplace(dis[v] = d + a3, v);
	}
}
int dp[(1 << 16) + 5][17];
inline void solve()
{
	memset(dp, 0x3f, sizeof(dp));
	for (int i = 0; i < 16; ++i)
		dp[1 << i][i] = dis[i];
	for (int S = 0; S < (1 << 16); ++S)
	{
		for (int i = 0; i < 16; ++i)
			for (int j = 0; j < 16; ++j)
			{
				if (i == j)
					continue;
				if (((S >> i) & 1) && ((S >> j) & 1))
					dp[S][i] = min(dp[S][i], dp[S ^ (1 << i)][j] + dis[i ^ j]);
			}
	}
}
inline void _main()
{
	int n;
	cin >> n;
	int S = 0;
	for (int i = 0; i < n; ++i)
	{
		string s, t;
		cin >> s >> t;
		int j = ((s[0] == '0') << 3) + ((s[1] == '0') << 2) + ((t[0] == '0') << 1) + ((t[1] == '0'));
		S |= (1 << j);
	}
	int res = 0x3f3f3f3f;
	for (int i = 0; i < 16; ++i)
		if ((S >> i) & 1)
			res = min(res, dp[S][i]);
	cout << res << '\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int test = 1;
	cin >> test >> a0 >> a1 >> a2 >> a3;
	init(), solve();
	while (test--)
		_main();
	return 0;
}