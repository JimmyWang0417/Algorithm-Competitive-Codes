#include <bits/stdc++.h>
using namespace std;
constexpr int N = (1 << 13) + 5;
typedef long double ld;
int n, a[N];
vector<int> g[N];
inline bool check(const vector<int> &a0, const vector<int> &a1)
{
	for (int i = 0, j = 0; i < (int)a0.size(); ++i)
	{
		while (j < (int)a1.size() && a0[i] > a1[j])
			++j;
		if (j < (int)a1.size() && a0[i] == a1[j])
			return true;
	}
	return false;
}
inline int dfs(int dep, int use)
{
	if (dep == 0)
		return use;
	vector<int> p;
	for (int i = (1 << (dep - 1)); i < (1 << dep); ++i)
	{
		int lc = i << 1, rc = i << 1 | 1;
		if (check(g[lc], g[rc]))
			p.emplace_back(i);
		else
		{
			g[i].resize(g[lc].size() + g[rc].size());
			merge(g[lc].begin(), g[lc].end(), g[rc].begin(), g[rc].end(), g[i].begin());
		}
	}
	use += (int)p.size();
	if (use > n - dep + 1)
		return INT_MAX;
	int ans = INT_MAX;
	for (int i = 0; i < (1 << p.size()); ++i)
	{
		for (int j = 0; j < (int)p.size(); ++j)
			g[p[j]] = g[p[j] << 1 | ((i >> j) & 1)];
		ans = min(ans, dfs(dep - 1, use));
	}
	return ans;
}
inline void _main()
{
	cin >> n;
	for (int i = 2; i < (1 << (n + 1)); ++i)
	{
		cin >> a[i];
		a[i] += a[i >> 1];
	}
	for (int i = (1 << n); i < (1 << (n + 1)); ++i)
		g[i].push_back(a[i]);
	int res = dfs(n, 0);
	cout << (res > n ? -1 : res) << '\n';
	for (int i = 1; i < (1 << (n + 1)); ++i)
	{
		g[i].clear();
		a[i] = 0;
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