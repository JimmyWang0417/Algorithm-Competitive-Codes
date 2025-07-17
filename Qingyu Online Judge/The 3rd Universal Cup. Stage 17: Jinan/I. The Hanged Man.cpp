#include <bits/stdc++.h>
using namespace std;
constexpr int N = 3e5 + 5;
int n;
int leave[N];
vector<int> g[N];
pair<int, int> p[N];
int tot;
inline void dfs(int u, int _fa)
{
	leave[u] = 0;
	for (int v : g[u])
	{
		if (v == _fa)
			continue;
		dfs(v, u);
	}
	sort(g[u].begin(), g[u].end(), [](int x, int y) { return (leave[x] == x) > (leave[y] == y); });
	for (auto v : g[u])
	{
		if (v == _fa)
			continue;
		if (leave[v])
		{
			if (leave[u])
			{
				p[++tot] = make_pair(leave[u], leave[v]);
				leave[u] = 0;
			}
			else
				leave[u] = leave[v];
		}
	}
	if (!leave[u])
		leave[u] = u;
}
inline void work()
{
	for (int i = 1; i <= n; ++i)
		g[i].clear();
	tot = 0;
	cin >> n;
	for (int i = 1; i < n; ++i)
	{
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	int root = 1;
	for (int i = 2; i <= n; ++i)
		if (g[i].size() % 2 == 0)
			root = i;
	dfs(root, 0);
	if (leave[root])
	{
		for (auto v : g[root])
			if (v == leave[root])
			{
				cout << "-1\n";
				return;
			}
	}
	cout << tot << '\n';
	for (int i = 1; i <= tot; ++i)
		cout << p[i].first << ' ' << p[i].second << '\n';
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