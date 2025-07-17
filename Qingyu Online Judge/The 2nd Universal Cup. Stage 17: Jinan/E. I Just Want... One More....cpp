#include <bits/stdc++.h>
using namespace std;
constexpr int N = 4e5 + 5;
typedef long long ll;
int n, m;
struct Edge
{
	int next, to, flow, cap;
} edge[N * 2];
int head[N], num_edge = 1;
inline void add_edge(int from, int to, int cap, bool flag = true)
{
	edge[++num_edge].next = head[from];
	edge[num_edge].to = to;
	edge[num_edge].flow = 0;
	edge[num_edge].cap = cap;
	head[from] = num_edge;
	if (flag)
		add_edge(to, from, 0, false);
}
int S, T;
int dis[N], cur[N];
inline bool bfs()
{
	for (int i = S; i <= T; ++i)
	{
		dis[i] = 0;
		cur[i] = head[i];
	}
	queue<int> q;
	q.push(S);
	dis[S] = 1;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		if (u == T)
			return true;
		for (int i = head[u]; i; i = edge[i].next)
		{
			int v = edge[i].to;
			if (!dis[v] && edge[i].cap > edge[i].flow)
			{
				dis[v] = dis[u] + 1;
				q.push(v);
			}
		}
	}
	return false;
}
inline int dinic(int u, int flow)
{
	if (u == T)
		return flow;
	int res = 0;
	for (int &i = cur[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (dis[v] == dis[u] + 1 && edge[i].cap > edge[i].flow)
		{
			int f = dinic(v, min(flow, edge[i].cap - edge[i].flow));
			if (f)
			{
				res += f;
				flow -= f;
				edge[i].flow += f;
				edge[i ^ 1].flow -= f;
				if (!flow)
					break;
			}
		}
	}
	return res;
}
inline int maxflow()
{
	int res = 0;
	while (bfs())
		res += dinic(S, INT_MAX);
	return res;
}
int belong[N];
bool exist[N];
inline void work()
{
	cin >> n >> m;
	S = 0, T = 2 * n + 1;
	for (int i = 1; i <= m; ++i)
	{
		int u, v;
		cin >> u >> v;
		add_edge(u, v + n, 1);
	}
	for (int i = 1; i <= n; ++i)
	{
		add_edge(S, i, 1);
		add_edge(i + n, T, 1);
	}
	maxflow();
	for (int i = 1; i <= m; ++i)
	{
		int u = edge[i << 1 | 1].to, v = edge[i << 1].to;
		if (edge[i << 1].flow != edge[i << 1].cap)
			continue;
		belong[u] = v;
		belong[v] = u;
	}
	queue<int> q;
	for (int i = 1; i <= 2 * n; ++i)
	{
		if (!belong[i])
		{
			q.push(i);
			exist[i] = true;
		}
	}
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = head[u]; i; i = edge[i].next)
		{
			int v = belong[edge[i].to];
			if (v && !exist[v])
			{
				q.push(v);
				exist[v] = true;
			}
		}
	}
	int cnt1 = 0, cnt2 = 0;
	for (int i = 1; i <= n; ++i)
	{
		if (exist[i])
			++cnt1;
	}
	for (int i = n + 1; i <= 2 * n; ++i)
	{
		if (exist[i])
			++cnt2;
	}
	cout << (ll)cnt1 * cnt2 << '\n';
	num_edge = 1;
	for (int i = S; i <= T; ++i)
		head[i] = 0;
	for (int i = 1; i <= 2 * n; ++i)
		belong[i] = exist[i] = false;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int test = 1;
	cin >> test;
	while (test --)
		work();
	return 0;
}