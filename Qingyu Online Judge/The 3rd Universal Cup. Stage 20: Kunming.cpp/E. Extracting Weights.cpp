#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 255;
constexpr int mod = 998244353;
int n, m; 
bitset<N> a[N], b[N];
pair<int, int> c[N];
vector<int> g[N];
int all;
inline void insert(bitset<N> x, int u, int v)
{
	bitset<N> y;
	for (int i = n - 1; i >= 0; --i)
	{
		if (x[i])
		{
			if (a[i].any())
			{
				x ^= a[i];
				y ^= b[i];
			}
			else
			{
				y[i] = true;
				a[i] = x;
				b[i] = y;
				c[i] = make_pair(u, v);
				++all;
				break;
			}
		}
	}
}
inline void solve()
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < i; ++j)
			if (a[i][j])
			{
				a[i] ^= a[j];
				b[i] ^= b[j];
			}
}
inline void dfs(int u, int _fa, int d, int root, bitset<N> res)
{
	res[u - 1] = true;
	if (d == m)
	{
		insert(res, u, root);
		return;
	}
	for (int v : g[u])
	{
		if (v == _fa)
			continue;
		dfs(v, u, d + 1, root, res);
	}
}
int d[N];
inline void _main()
{
	cin >> n >> m;
	for (int i = 1; i < n; ++i)
	{
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	insert(bitset<N>("1"), 0, 0);
	for (int i = 1; i <= n; ++i)
		dfs(i, 0, 0, i, bitset<N>());
	if (all == n)
	{
		solve();
		cout << "YES\n";
		cout << "? " << n - 1;
		for (int i = 1; i < n; ++i)
			cout << ' ' << c[i].first << ' ' << c[i].second;
		cout << endl;
		for (int i = 1; i < n; ++i)
			cin >> d[i];
		cout << "!";
		for (int i = 1; i < n; ++i)
		{
			int res = 0;
			for (int j = 0; j < n; ++j)
				if (b[i][j])
					res ^= d[j];
			cout << ' ' << res;
		}
		cout << endl;
	}
	else
		cout << "NO\n";
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