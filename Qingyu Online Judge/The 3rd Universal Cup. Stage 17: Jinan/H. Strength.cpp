#include <bits/stdc++.h>
using namespace std;
constexpr int N = 23;
typedef long long ll;
ll dp[N][3][2];
int dightx[N], totx;
int dighty[N], toty;
int n;
pair<int, int> p[N];
int tot;
int dight[3][10][10];
inline void work()
{
	ll x, y;
	cin >> x >> y;
	while (x)
	{
		dightx[++totx] = x % 10;
		x /= 10;
	}
	while (y)
	{
		dighty[++toty] = y % 10;
		y /= 10;
	}
	for (int ad = 0; ad <= 2; ++ad)
		for (int i = 0; i <= 9; ++i)
		{
			tot = 0;
			if (ad % 2 == 0)
			{
				p[tot++] = make_pair(0, i >= 5);
				p[tot++] = make_pair(0, i >= 5);
				p[tot++] = make_pair(0, (i + 0) >= 5);
				p[tot++] = make_pair((i + 0) % 10, (i + 0) >= 10);
			}
			if (ad)
			{
				p[tot++] = make_pair(0, i >= 5);
				p[tot++] = make_pair(1, i >= 5);
				p[tot++] = make_pair(0, (i + 1) >= 5);
				p[tot++] = make_pair((i + 1) % 10, (i + 1) >= 10);
			}
			sort(p, p + tot);
			tot = (int)(unique(p, p + tot) - p);
			
			int cnt = 0;
			for (int j = 1; j < tot; ++j)
			{
				if (p[cnt].first == p[j].first)
					p[cnt].second = 2;
				else
					p[++cnt] = p[j];
			}
			for (int j = 0; j <= cnt; ++j)
				dight[ad][i][p[j].first] = p[j].second + 1;
		}
	n = max(totx, toty);
	dp[1][0][0] = dp[1][0][1] = 1;
	for (int u = 1; u <= n; ++u)
		for (int ad = 0; ad <= 2; ++ad)
			for (int limit = 0; limit <= 1; ++limit)
			{
				int maxx = limit ? dighty[u] : 9;
				for (int i = 0; i <= maxx; ++i)
				{
					if (dight[ad][i][dightx[u]])
						dp[u + 1][dight[ad][i][dightx[u]] - 1][limit] += dp[u][ad][limit && (i == maxx)];
				}
			}
	cout << dp[n + 1][0][1] + dp[n + 1][1][1] + dp[n + 1][2][1] << '\n';
	memset(dp, 0, sizeof(dp));
	memset(dightx, 0, sizeof(dightx));
	memset(dighty, 0, sizeof(dighty));
	totx = toty = 0;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--)
		work();
	return 0;
}