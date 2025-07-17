#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 2e5 + 5;
int n, m;
vector<int> g[N];
vector<int> vis[N];
inline void _main()
{
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			int x;
			cin >> x;
			g[j].push_back(x);
		}
	for (int i = 0; i < m; ++i)
	{
		sort(g[i].begin(), g[i].end());
		vis[i].resize(n);
	}
	int cnt = 0;
	for (int i = 1; i < m; ++i)
	{
		for (int j = 0, k = 0; j < n; ++j)
		{
			while (k < n && (vis[i - 1][k] || g[i - 1][k] <= g[i][j]))
				++k;
			if (k < n)
			{
				vis[i][j] = true;
				++cnt;
				++k;
			}
		}
	}
	if (cnt >= n)
		cout << "YES\n";
	else
		cout << "NO\n";
	for (int i = 0; i < m; ++i)
	{
		g[i].clear();
		vis[i].clear();
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