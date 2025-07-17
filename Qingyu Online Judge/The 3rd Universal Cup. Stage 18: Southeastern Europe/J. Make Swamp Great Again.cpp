#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e5 + 5;
int n, a[N], b[N];
int p[N], tot;
vector<int> g[N];
inline void _main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		p[++tot] = a[i];
	}
	sort(p + 1, p + 1 + tot);
	tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
	for (int i = 1; i <= n; ++i)
	{
		a[i] = (int)(lower_bound(p + 1, p + 1 + tot, a[i]) - p);
		g[a[i]].push_back(i);
	}
	for (int i = 1; i <= tot; ++i)
	{
		bool flag = true;
		for (int j : g[i])
		{
			if (a[j % n + 1] >= a[j] && a[(j + 1) % n + 1] >= a[j])
			{
				flag = false;
				break;
			}
			if (a[j % n + 1] <= a[j] && a[(j + 1) % n + 1] <= a[j])
			{
				flag = false;
				break;
			}
			if (a[(j - 2 + n) % n + 1] >= a[j] && a[(j - 3 + n) % n + 1] >= a[j])
			{
				flag = false;
				break;
			}
			if (a[(j - 2 + n) % n + 1] <= a[j] && a[(j - 3 + n) % n + 1] <= a[j])
			{
				flag = false;
				break;
			}
			if (a[(j - 2 + n) % n + 1] >= a[j] && a[j % n + 1] >= a[j])
			{
				flag = false;
				break;
			}
			if (a[(j - 2 + n) % n + 1] <= a[j] && a[j % n + 1] <= a[j])
			{
				flag = false;
				break;
			}
		}
		for (int j : g[i])
			b[j] = n - (int)g[i].size() + flag;
	}
	for (int i = 1; i <= n; ++i)
		cout << b[i] << ' ';
	cout << '\n';
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