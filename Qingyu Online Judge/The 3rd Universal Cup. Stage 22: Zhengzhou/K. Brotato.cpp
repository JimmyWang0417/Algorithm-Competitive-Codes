#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e5 + 5;
constexpr int mod = 998244353;
int n, k;
long double p;
long double _buf[2][N], E0[N];
inline void _main()
{
	cin >> n >> k >> p;
	if (k > 165)
	{
		printf("%.10Lf\n", n / (1 - p));
		return;
	}
	auto f = _buf[0], g = _buf[1];
	E0[0] = 1;
	for (int i = 1; i <= n; ++i)
		E0[i] = E0[i - 1] * (1 / (1 - p));
	for (int i = n; i >= 1; --i)
		f[i] = f[i + 1] + E0[i];
	for (int j = 1; j <= k; ++j)
	{
		swap(f, g);
		for (int i = n; i >= 1; --i)
			f[i] = min(1 + p * g[i] + (1 - p) * f[i + 1], E0[i] + f[i + 1]);
	}
	printf("%.10Lf\n", f[1]);
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