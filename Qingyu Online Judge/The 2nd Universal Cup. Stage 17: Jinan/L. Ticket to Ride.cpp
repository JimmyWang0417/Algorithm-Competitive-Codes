#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e4 + 5;
constexpr int base = 1e6 + 33;
constexpr int mod = 998244353;
typedef long long ll;
typedef unsigned long long ull;
int n, m;
vector<pair<int, int>> G[N];
struct node
{
	int fa[N], nxt[N];
	int maxpos;
	ll max, c[N];
	inline int find(int x)
	{
		return fa[x] == x ? x : fa[x] = find(fa[x]);
	}
	inline void clear()
	{
		max = maxpos = 0;
		for (int i = 1; i <= n; ++i)
		{
			fa[i] = i;
			c[i] = nxt[i] = 0;
		}
	}
	inline void insert(int pos, ll k)
	{
		if (k > max)
		{
			c[maxpos] = k - max;
			nxt[maxpos] = pos;
			maxpos = pos;
			max = k;
		}
		else
			fa[pos] = maxpos;
	}
	inline void update(int u, ll k)
	{
		u = find(u);
		while (u != maxpos)
		{
			if (k < c[u])
			{
				c[u] -= k;
				k = 0;
				break;
			}
			k -= c[u];
			int v = nxt[u];
			if (v == maxpos)
				maxpos = u;
			else
			{
				nxt[u] = nxt[v];
				c[u] = c[v];
			}
			fa[v] = u;
		}
		if (u == maxpos)
			max += k;
	}
} q;
ll buf[2][N];
ll answer[N];
inline void clear()
{
	for (int i = 0; i <= n; ++i)
	{
		G[i].clear();
		buf[0][i] = buf[1][i] = answer[i] = 0;
	}
}
inline void work()
{
	cin >> n >> m;
	for (int i = 1; i <= m; ++i)
	{
		int l, r, v;
		cin >> l >> r >> v;
		G[r].emplace_back(l, v);
	}
	auto f = buf[0], g = buf[1];
	for (int r = 1; r <= n; ++r)
	{
		f[r] = f[r - 1];
		for (auto [l, v] : G[r])
			f[r] += v;
	}
	answer[n] = f[n];
	for (int j = 1; j < n; ++j)
	{
		q.clear();
		swap(f, g);
		for (int i = j; i <= n; ++i)
		{
			for (auto [l, v] : G[i])
				if (l >= j)
					q.update(l, v);
			f[i] = max(g[i - 1], q.max);
			q.insert(i, f[i]);
		}
		answer[n - j] = f[n];
	}
	for (int i = 1; i <= n; ++i)
		cout << answer[i] << ' ';
	cout << '\n';
	clear();
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