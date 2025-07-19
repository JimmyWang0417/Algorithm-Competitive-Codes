#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
template <typename T>
inline void add(T &x, T y)
{
	x += y;
	if (x >= mod)
		x -= mod;
}
template <typename T>
inline void del(T &x, T y)
{
	x -= y;
	if (x < 0)
		x += mod;
}
int n;
pair<int, int> a[N];
int px[N], totx;
int py[N], toty;
struct Edge
{
	int next, to;
	bool vis;
} edge[N * 2];
int head[N], num_edge = 1;
inline void add_edge(int from, int to)
{
	edge[++num_edge].next = head[from];
	edge[num_edge].to = to;
	edge[num_edge].vis = false;
	head[from] = num_edge;
}
bool vis[N];
pair<int, int> match[N];
int tot;
bool exist[N];
inline void merge(int u, int v)
{
	match[++tot] = make_pair(u, v);
	edge[u << 1].vis = edge[u << 1 | 1].vis = true;
	edge[v << 1].vis = edge[v << 1 | 1].vis = true;
}
inline void dfs(int u, int lastedge)
{
	vis[u] = true;
	for (int i = head[u]; i; i = edge[i].next)
	{
		int v = edge[i].to;
		if (!vis[v])
			dfs(v, i);
	}
	vector<int> son;
	for (int i = head[u]; i; i = edge[i].next)
	{
		if (i == (lastedge ^ 1) || edge[i].vis)
			continue;
		son.push_back(i >> 1);
	}
	if (lastedge && (son.size() & 1))
		son.push_back(lastedge >> 1);
	for (int i = 1; i < (int)son.size(); i += 2)
		merge(son[i - 1], son[i]);
}
inline void work()
{
	cin >> n;
	for (int i = 1; i <= 2 * n; ++i)
	{
		cin >> a[i].first >> a[i].second;
		px[++totx] = a[i].first;
		py[++toty] = a[i].second;
	}
	sort(px + 1, px + 1 + totx);
	totx = (int)(unique(px + 1, px + 1 + totx) - px - 1);
	sort(py + 1, py + 1 + toty);
	toty = (int)(unique(py + 1, py + 1 + toty) - py - 1);
	for (int i = 1; i <= 2 * n; ++i)
	{
		int x = (int)(lower_bound(px + 1, px + 1 + totx, a[i].first) - px);
		int y = (int)(lower_bound(py + 1, py + 1 + toty, a[i].second) - py);
		add_edge(x, totx + y);
		add_edge(totx + y, x);
	}
	for (int i = 1; i <= totx + toty; ++i)
		if (!vis[i])
			dfs(i, 0);
	cout << tot << '\n';
	for (int i = 1; i <= tot; ++i)
	{
		cout << match[i].first << ' ' << match[i].second << '\n';
		exist[match[i].first] = exist[match[i].second] = true;
	}
	for (int i = 1, j = 0; i <= 2 * n; ++i)
	{
		if (exist[i])
			continue;
		if (j)
		{
			cout << j << ' ' << i << '\n';
			j = 0;
		}
		else
			j = i;
	}
	for (int i = 1; i <= tot; ++i)
		exist[match[i].first] = exist[match[i].second] = false;
	for (int i = 1; i <= totx + toty; ++i)
		head[i] = vis[i] = 0;
	num_edge = 1;
	tot = 0;
	totx = toty = 0;
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