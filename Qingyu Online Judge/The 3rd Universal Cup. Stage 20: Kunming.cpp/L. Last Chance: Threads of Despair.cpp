#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
int n, m; 
int a[N], b[N];
inline void _main()
{
	cin >> n >> m;
	int unused = n;
	bool zero = false;
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		--a[i];
		if (a[i] == 0)
		{
			if (!zero)
				zero = true;
			else
				--unused;
		}
	}
	for (int i = 1; i <= m; ++i)
		cin >> b[i];
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + m);
	int cnt = 0;
	for (int i = 1, j = 1; i <= m; ++i)
	{
		while (j <= n && a[j] <= cnt)
		{
			++j;
			++cnt;
		}
		if (unused + cnt < b[i])
		{
			cout << "No\n";
			return;
		}
		else
		{
			unused -= max(b[i] - cnt, 0);
			++cnt;
		}
	}
	cout << "Yes\n";
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