#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5e5 + 5;
int n, m, q;
struct Edge
{
	int next, to, dis;
} edge[N];
int head[N], num_edge;
inline void add_edge(int from, int to, int dis)
{
	edge[++num_edge].next = head[from];
	edge[num_edge].to = to;
	edge[num_edge].dis = dis;
	head[from] = num_edge;
}
int dfn[N], low[N], dfstime;
int st[N], top;
bool dp[N];
int belong[N], color;
long long dis[N];
inline void tarjan(int u)
{
	st[++top] = u;
	dfn[u] = low[u] = ++dfstime;
	for (int i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (!dfn[v])
		{
			dis[v] = dis[u] + edge[i].dis;
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if (!belong[v])
		{
			low[u] = min(low[u], dfn[v]);
			if (dis[v] != dis[u] + edge[i].dis)
				dp[v] = true;
		}
		dp[u] |= dp[v];
	}
	if (dfn[u] == low[u])
	{
		belong[u] = ++color;
		while (st[top] != u)
		{
			int v = st[top--];
			belong[v] = color;
			dp[v] |= dp[u];
		}
		--top;
	}
}
inline void _main()
{
	cin >> n >> m >> q;
	for (int i = 1; i <= m; ++i)
	{
		int u, v;
		cin >> u >> v;
		add_edge((u % n + n - 1) % n + 1, ((u + v) % n + n - 1) % n + 1, v);
	}
	for (int i = 1; i <= n; ++i)
		if (!dfn[i])
			tarjan(i);
	for (int i = 0; i < q; ++i)
	{
		int x;
		cin >> x;
		cout << (dp[(x % n + n - 1) % n + 1] ? "Yes\n" : "No\n");
	}
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