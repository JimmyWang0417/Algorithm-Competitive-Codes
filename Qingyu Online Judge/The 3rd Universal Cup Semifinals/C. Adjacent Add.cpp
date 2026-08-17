#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
constexpr int mod1 = 998244353;
constexpr int mod2 = 1e9 + 7;
auto _main()
{
	int n, m;
	cin >> n >> m;
	vector<int> a(n + 5);
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	double res0 = 0, res1 = 0;
	for (int i = n; i >= 1; --i)
	{
		res0 = 1 - res0 / m;
		res1 = a[i] - res1 / m;
	}
	int res = (int)(res1 / res0);
	auto check = [&](int x)
	{
		i64 res1 = 0, res2 = 0;
		for (int i = 1; i <= n; ++i)
		{
			res1 = (res1 * (-m) + (x - a[i])) % mod1;
			res2 = (res2 * (-m) + (x - a[i])) % mod1;
		}
		return res1 == 0 && res2 == 0;
	};
	for (int i = res - 10; i <= res + 10; ++i)
		if (check(i))
		{
			cout << "Yes\n";
			return;
		}
	cout << "No\n";
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
