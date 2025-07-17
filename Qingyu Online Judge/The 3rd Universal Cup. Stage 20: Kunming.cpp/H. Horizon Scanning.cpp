#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
int n, m;
double a[N];
inline void _main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
	{
		int x, y;
		cin >> x >> y;
		a[i] = atan2(y, x);
	}
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n; ++i)
		a[i + n] = a[i] + 2 * M_PI;
	double ans = 0;
	for (int i = 1; i <= n; ++i)
	{
		double res = a[i + m] - a[i];
		if (ans < res)
			ans = res;
	}
	printf("%.8lf\n", ans);
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