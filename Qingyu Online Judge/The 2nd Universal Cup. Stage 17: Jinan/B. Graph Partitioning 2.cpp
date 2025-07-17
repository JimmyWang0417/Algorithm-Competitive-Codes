#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
constexpr int N = 1e5 + 5;
constexpr int M = 323;
constexpr int mod = 998244353;
typedef long long ll;
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
namespace subtask1
{
	int sze[N];
	__gnu_pbds::gp_hash_table<int, int> dp[N], g;
	inline void dfs(int u, int _fa)
	{
		dp[u].clear();
		dp[u][1] = 1;
		sze[u] = 1;
		for (int i = head[u]; i; i = edge[i].next)
		{
			int v = edge[i].to;
			if (v == _fa)
				continue;
			dfs(v, u);
			for (auto [j, l] : dp[u])
				for (auto [k, r] : dp[v])
					if (j + k <= m + 1)
						g[j + k] = (int)((g[j + k] + (ll)l * r) % mod);
			swap(dp[u], g);
			g.clear();
			sze[u] += sze[v];
		}
		dp[u][0] = (dp[u][m] + dp[u][m + 1]) % mod;
		dp[u].erase(m + 1);
		if (!dp[u][0])
			dp[u].erase(0);
	}
	inline void main()
	{
		dfs(1, 0);
		cout << dp[1][0] << '\n';
	}
}
namespace subtask2
{
	
}
inline void work()
{
	cin >> n >> m;
	for (int i = 1; i < n; ++i)
	{
		int u, v;
		cin >> u >> v;
		add_edge(u, v);
		add_edge(v, u);
	}
	subtask1::main();
	for (int i = 1; i <= n; ++i)
		head[i] = 0;
	num_edge = 0;
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