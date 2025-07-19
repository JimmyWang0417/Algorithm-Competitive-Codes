#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5 + 5;
int n, m;
struct Edge
{
	int next, to;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
	edge[++num_edge].next = head[from];
	edge[num_edge].to = to;
	head[from] = num_edge;
}
int dfn[N], dfstime;
int dep[N];
int sze[N];
auto lowbit = [](int x)
{
	return x & (-x);
};
int fa[N];
int c[N];
inline void update(int pos, int val)
{
//	printf("%d\n", pos);
	for (int i = pos; i <= n; i += lowbit(i))
		c[i] += val;
}
inline int query(int pos)
{
	int res = 0;
	for (int i = pos; i; i -= lowbit(i))
		res += c[i];
	return res;
}
inline int query(int l, int r)
{
	return query(r) - query(l - 1);
}
inline void dfs(int u, int _fa)
{
	dep[u] = dep[fa[u] = _fa] + 1;
	dfn[u] = ++dfstime;
	sze[u] = 1;
	for (int i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (v == _fa)
			continue;
		dfs(v, u);
		sze[u] += sze[v];
	}
}
int p[N], tot;
inline bool check(int l, int r)
{
	int u = p[l++];
	while(l <= r)
	{
		if(fa[p[l]] != u)
			return false;
		int mid = min(r, l + sze[p[l]] - 1);
		if(!check(l, mid))
			return false;
		l = mid + 1;
	}
	return true;
}
inline void work()
{
	cin >> tot;
	bool flag = true;
	for (int i = 1; i <= tot; ++i)
	{
		cin >> p[i];
		int u = p[i];
		if (query(dfn[u], dfn[u] + sze[u] - 1) > 0)
			flag = false;
		update(dfn[u], 1);
	}
//	for (int i = 1; i <= tot; ++i)
//		printf("%d %d\n", p[i], dfn[p[i]]);
	for (int i = 1; i <= tot; ++i)
		update(dfn[p[i]], -1);
	vector<int> g;
	int o = 1;
	while(o <= tot)
	{
		flag &= check(o, min(tot, o + sze[p[o]] - 1));
		g.push_back(fa[p[o]]);
		o += sze[p[o]];
	}
	auto nmsl = [](int x, int y)
	{
		return dfn[y] <= dfn[x] && dfn[x] < dfn[y] + sze[y];
	};
	for (int i = 1; i < (int)g.size(); ++i)
		flag &= nmsl(g[i - 1], g[i]);
	if (flag)
		cout << "Yes\n";
	else
		cout << "No\n";
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i < n; ++i)
	{
		int u, v;
		cin >> u >> v;
		add_edge(u, v);
		add_edge(v, u);
	}
	dfs(1, 0);
//	for (int i = 1; i <= n; ++i)
//		printf("%d ", dfn[i]);
//	putchar('\n');
	while (m--)
		work();
	return 0;
}