#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N = 1e6 + 5;
inline void _main()
{
	int n, m;
	cin >> n >> m;
	if (n == 1 && m == 1)
		cout << "Yes\n1\n";
	else if ((n % 2 == 0 && m % 2 == 1) || m == 1)
		cout << "No\n";
	else
	{
		vector<vector<int>> a(n + 5);
		for (int i = 1; i <= n; ++i)
			a[i].resize(m + 5);
		if (m & 1)
		{
			for (int i = 1; i <= n; ++i)
				a[i][1] = i;
			int cnt = n;
			for (int i = (n + 1) / 2 + 1; i <= n; ++i)
				a[i][2] = ++cnt;
			for(int i = 1; i <= (n + 1) / 2; ++i)
				a[i][2] = ++cnt;
			int all = 3 * (n * 3 + 1) / 2;
			for (int i = 1; i <= n; ++i)
				a[i][3] = all - a[i][1] - a[i][2];
		}
		for (int i = (m & 1 ? 4 : 1); i <= m; ++i)
		{
			if (i & 1)
				for (int j = 1; j <= n; ++j)
					a[j][i] = (i - 1) * n + j;
			else
				for (int j = n; j >= 1; --j)
					a[n - j + 1][i] = j + (i - 1) * n;
		}
		cout << "Yes\n";
		for (int i = 1; i <= n; ++i)
		{
			for (int j = 1; j <= m; ++j)
				cout << a[i][j] << ' ';
			cout << '\n';
		}
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