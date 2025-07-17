#include <bits/stdc++.h>
using namespace std;
int a[4];
bool vis[4];
int answer;
int w, h, s;
inline void dfs(int u, vector<int> g, int res)
{
	if (u == 4)
	{
		answer = min(answer, res);
		return;
	}
	for (int i = 0; i < (1 << g.size()); ++i)
	{
		int sum = 0;
		vector<int> h;
		for (int j = 0; j < (int)g.size(); ++j)
			if ((i >> j) & 1)
				sum += g[j];
			else
				h.push_back(g[j]);
		for (int j = 0; j < 4; ++j)
		{
			if (vis[j] || sum > a[j])
				continue;
			vis[j] = true;
			int leave = a[j] - sum, ad = leave ? (leave - 1) / s + 1 : 0;
			vector<int> f = h;
			f.push_back(ad * s - leave);
			dfs(u + 1, f, res + ad);
			vis[j] = false;
		}
	}
}
inline void work()
{
	cin >> w >> h >> s;
	a[0] = w, a[1] = w, a[2] = h, a[3] = h;
	answer = 0x7fffffff;
	dfs(0, vector<int>(), 0);
	cout << answer << '\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T = 1;
	cin >> T;
	while (T--)
		work();
	return 0;
}