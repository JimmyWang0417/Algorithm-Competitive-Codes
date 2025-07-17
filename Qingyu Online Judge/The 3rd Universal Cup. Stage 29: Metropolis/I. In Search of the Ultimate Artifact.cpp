#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
int a[N];
inline void _main()
{
	int n, k;
	cin >> n >> k;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	sort(a + 1, a + 1 + n, greater<int>());
	ll res = a[1] % mod, ans = res;
	for (int i = 1; 1 + i * (k - 1) <= n; ++i)
	{
		bool flag = true;
		for (int j = 1 + (i - 1) * (k - 1) + 1; j <= 1 + i * (k - 1); ++j)
		{
			(res *= a[j]) %= mod;
			if (!a[j])
				flag = false;
		}
		if (!flag)
			break;
		ans = res;
	}
	cout << ans << '\n';
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