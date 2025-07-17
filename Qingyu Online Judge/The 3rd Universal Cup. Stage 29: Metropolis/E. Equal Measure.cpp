#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
int n, m;
vector<int> g[N];
int dfn[N], dep[N], dfstime;
bool answer;
int len;
int fa[N][23];
inline int getlca(int u, int v)
{
	if (dep[u] < dep[v])
		swap(u, v);
	for (int i = 20; i >= 0; --i)
		if (dep[fa[u][i]] >= dep[v])
			u = fa[u][i];
	if (u == v)
		return u;
	for (int i = 20; i >= 0; --i)
		if (fa[u][i] != fa[v][i])
		{
			u = fa[u][i];
			v = fa[v][i];
		}
	return fa[u][0];
}
vector<pair<int, int>> p;
inline void dfs(int u, int _fa)
{
	fa[u][0] = _fa;
	for (int i = 0; i < 20; ++i)
		fa[u][i + 1] = fa[fa[u][i]][i];
	dfn[u] = ++dfstime;
	dep[u] = dep[_fa] + 1;
	for (int v : g[u])
	{
		if (v == _fa)
			continue;
		if (!dfn[v])
			dfs(v, u);
		else if (dep[v] < dep[u])
		{
			if (!len)
				len = dep[u] - dep[v] + 1;
			else if (len != dep[u] - dep[v] + 1)
				answer = false;
			p.emplace_back(u, v);
		}
	}
}
inline void _main()
{
	cin >> n >> m;
	for (int i = 1; i <= m; ++i)
	{
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	answer = true, len = 0;
	for (int i = 1; i <= n; ++i)
		if (!dfn[i])
			dfs(i, 0);
	sort(p.begin(), p.end(), [](auto x, auto y) {return dfn[x.first] < dfn[y.first]; });
	for (int i = 1; i < (int)p.size(); ++i)
		for (int j = i - 1; j >= 0 && j >= i - 10; --j)
	{
		auto [u1, v1] = p[j];
		auto [u2, v2] = p[i];
		int u = getlca(u1, u2), v = (dep[v1] > dep[v2] ? v1 : v2);
		if (dep[u] > dep[v])
		{
			int l = dep[u] - dep[v];
			if (l * 2 != len)
				answer = false;
		}
	}
	cout << (answer ? "Yes\n" : "No\n");
	p.clear();
	dfstime = 0;
	for (int i = 1; i <= n; ++i)
	{
		g[i].clear();
		dfn[i] = dep[i] = 0;
		for (int j = 0; j <= 20; ++j)
			fa[i][j] = 0;
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int test = 1;
	cin >> test;
	while (test--)
		_main();
	return 0;
}