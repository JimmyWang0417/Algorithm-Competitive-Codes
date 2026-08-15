#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
constexpr int mod1 = 998244353;
constexpr int mod2 = 1e9 + 7;
auto _main()
{
	int n;
	cin >> n;
	vector<vector<int>> g(n + 5);
	for (int i = 2; i <= n; ++i)
	{
		int _fa;
		cin >> _fa;
		g[_fa].push_back(i);
	}
	vector<bool> col(n + 5);
	function<void(int)> dfs = [&](int u)
	{
		col[u] = true;
		for (int v : g[u])
		{
			dfs(v);
			col[u] = col[u] & !col[v];
		}
	};
	dfs(1);
	vector<pair<int, int>> answer;
	for (int i = 2; i <= n; ++i)
		if (col[i])
			answer.emplace_back(i, 1);
		else
			answer.emplace_back(1, i);
	cout << "Yes\n";
	cout << answer.size() << '\n';
	for (auto [x, y] : answer)
		cout << x << ' ' << y << '\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T = 1;
	cin >> T;
	while (T--)
		_main();
	return 0;
}
