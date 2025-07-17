#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N = 31;
constexpr int mod = 998244353;
template <typename T>
inline void add(T &x, T y)
{
	x += y;
	if (x >= mod)
		x -= mod;
}
int n, m;
int rcnt[N];
vector<int> r[N][N], invr[N][N];
vector<vector<int>> t[N];
inline vector<int> operator * (const vector<int> &lhs, const vector<int> &rhs)
{
	vector<int> res(n);
	for (int i = 0; i < n; ++i)
		res[i] = lhs[rhs[i]];
	return res;
}
inline void dfs(int u, const vector<int> &);
inline void init()
{
	for (int i = 0; i < n; ++i)
	{
		++rcnt[i];
		r[i][i].resize(n), invr[i][i].resize(n);
		for (int j = i; j < n; ++j)
			r[i][i][j] = invr[i][i][j] = j;
	}
}
inline bool contain(int u, const vector<int> &g)
{
	if (u == n)
		return true;
	int v = g[u];
	if (r[u][v].empty())
		return false;
	return contain(u + 1, invr[u][v] * g);
}
inline void add(int u, const vector<int> &g)
{
	if (contain(u, g))
		return;
	t[u].push_back(g);
	vector<int> h(n);
	for (int v = u; v < n; ++v)
		if (!r[u][v].empty())
			dfs(u, g * r[u][v]);
}
inline void dfs(int u, const vector<int> &g)
{
	int v = g[u];
	if (!r[u][v].empty())
		add(u + 1, invr[u][v] * g);
	else
	{
		++rcnt[u];
		r[u][v].resize(n), invr[u][v].resize(n);
		for (int w = u; w < n; ++w)
			invr[u][v][r[u][v][w] = g[w]] = w;
		for (auto f : t[u])
			dfs(u, f * g);
	}
}
int dp[N][N][N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	init();
	for (int i = 0; i < m; ++i)
	{
		vector<int> p(n);
		for (int j = 0; j < n; ++j)
		{
			cin >> p[j];
			--p[j];
		}
		add(0, p);
	}
	for (int x = 0; x < n; ++x)
		for (int y = x + 1; y < n; ++y)
			dp[n][x][y] = 1;
	for (int u = n - 1; u >= 0; --u)
		for (int v = 0; v < n; ++v)
		{
			if (r[u][v].empty())
				continue;
			for (int x = 0; x < n; ++x)
				for (int y = 0; y < n; ++y)
				{
					int nx = (x < u) ? x : r[u][v][x];
					int ny = (y < u) ? y : r[u][v][y];
					add(dp[u][nx][ny], dp[u + 1][x][y]);
				}
		}
	int res = 0;
	for (int x = 0; x < n; ++x)
		for (int y = 0; y < x; ++y)
			add(res, dp[0][x][y]);
	cout << res << '\n';
	return 0;
} 