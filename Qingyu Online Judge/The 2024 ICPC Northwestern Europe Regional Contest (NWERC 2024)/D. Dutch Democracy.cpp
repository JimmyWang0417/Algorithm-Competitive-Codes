#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 6e6 + 5;
inline ll quickpow(ll a, ll b, int p) 
{
	ll res = 1;
	while (b) 
	{
		if (b & 1) 
			res = res * a % p;
		a = a * a % p; b >>= 1;
	}
	return res;
}
int n, m, a[N];
ll dp[N];
inline void _main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		m += a[i];
	}
	sort(a + 1, a + 1 + n, greater<int>());
	m = m / 2 + 1;
	ll res = 0;
	dp[0] = 1;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = max(m - a[i], 0); j < m; ++j)
			res += dp[j];
		for(int j = m - 1; j >= a[i]; --j)
			dp[j] += dp[j - a[i]];
	}
	cout << res << '\n';
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