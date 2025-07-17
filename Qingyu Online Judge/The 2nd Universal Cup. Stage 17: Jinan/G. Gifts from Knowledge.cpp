#include <bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
constexpr int N = 2e6 + 5;
constexpr int mod = 1e9 + 7;
int n, m;
string a[N], b[N];
struct Edge
{
	int next, to;
} edge[N * 4];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
	edge[++num_edge].next = head[from];
	edge[num_edge].to = to;
	head[from] = num_edge;
}
inline bool check(string x, string y)
{
	for (int i = 0; i < m; ++i)
		if (x[i] == '1' && y[i] == '1')
			return true;
	return false;
}
int dfn[N], low[N], dfstime;
int belong[N], color;
int st[N], top;
inline void tarjan(int u)
{
	dfn[u] = low[u] = ++dfstime;
	st[++top] = u;
	for (int i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (!dfn[v])
		{
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else
			low[u] = min(low[u], dfn[v]);
	}
	if (dfn[u] == low[u])
	{
		belong[u] = ++color;
		while (st[top] != u)
			belong[st[top--]] = color;
	}
}
inline void clear()
{
	color = dfstime = num_edge = 0;
	for (int i = 1; i <= 2 * n; ++i)
		dfn[i] = low[i] = belong[i] = head[i] = 0;
}
inline void work()
{
	cin >> n >> m;
	int cnt = 0;
	int tot = 0;
	int res = 1;
	for (int i = 0; i < n; ++i)
	{
		string s;
		cin >> s;
		bool flag = false;
		for (auto j : s)
			if (j == '1')
			{
				flag = true;
				++cnt;
			}
		if (flag)
		{
			a[++tot] = s;
			b[tot] = s;
			reverse(b[tot].begin(), b[tot].begin() + m);
		}
		else
			res = (res * 2) % mod;
	}
	n = tot;
	if (cnt > m)
	{
		cout << 0 << '\n';
		return;
	}
	for (int i = 1; i <= n; ++i)
		for (int j = i + 1; j <= n; ++j)
		{
			if (check(a[i], a[j]))
			{
				add_edge(i, j + n);
				add_edge(j + n, i);
				
				add_edge(i + n, j);
				add_edge(j, i + n);
			}
			if (check(a[i], b[j]))
			{
				add_edge(i, j);
				add_edge(j, i);
				
				add_edge(i + n, j + n);
				add_edge(j + n, i + n);
			}
		}
	for (int i = 1; i <= 2 * n; ++i)
		if (!dfn[i])
			tarjan(i);
	for (int i = 1; i <= n; ++i)
		if (belong[i] == belong[i + n])
		{
			clear();
			cout << "0\n";
			return;
		}
	for (int i = 1; i <= color / 2; ++i)
		res = (res * 2) % mod;
	cout << res << '\n';
	clear();
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