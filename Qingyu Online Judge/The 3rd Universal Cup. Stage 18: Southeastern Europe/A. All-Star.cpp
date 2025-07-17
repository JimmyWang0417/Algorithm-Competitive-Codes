#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e3 + 5;
int n, root;
int deg[N];
vector<int> g[N];
inline void dfs(int u, int _fa)
{
	for (int v : g[u])
	{
		if (v == _fa)
			continue;
		cout << root << ' ' << u << ' ' << v << '\n';
		dfs(v, u);
	}
}
inline void _main()
{
	cin >> n;
	for (int i = 1; i < n; ++i)
	{
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	root = 1;
	for (int i = 2; i <= n; ++i)
		if (g[root].size() < g[i].size())
			root = i;
	cout << n - 1 - g[root].size() << '\n';
	for (int v : g[root])
		dfs(v, root);
	for (int i = 1; i <= n; ++i)
		g[i].clear();
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