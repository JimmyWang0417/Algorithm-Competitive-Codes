#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 3005;
constexpr int mod = 998244353;
int n, m, a[N];
ll fac[N], ifac[N];
inline ll quickpow(ll a, int b)
{
	ll res = 1;
	while (b)
	{
		if (b & 1)
			(res *= a) %= mod;
		(a *= a) %= mod;
		b >>= 1;
	}
	return res;
}
inline ll C(int _n, int _m)
{
	if (_m < 0 || _n < _m)
		return 0;
	return fac[_n] * ifac[_m] % mod * ifac[_n - _m] % mod;
}
int dp[N];
ll answer[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	sort(a + 1, a + 1 + n, greater<int>());
	fac[0] = 1;
	for (int i = 1; i <= n; ++i)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = quickpow(fac[n], mod - 2);
	for (int i = n; i >= 1; --i)
		ifac[i - 1] = ifac[i] * i % mod;
	dp[0] = 1;
	for (int i = 1; i <= n; ++i)
	{
		int res = dp[m];
		for (int j = m; j >= 0; --j)
			(dp[min(j + a[i], m)] += dp[j]) %= mod;
		for (int k = 0; k <= n; ++k)
			(answer[k] += (dp[m] - res + mod) * C(n - i, k)) %= mod;
	}
	for (int k = 0; k <= n; ++k)
		cout << answer[k] << '\n';
	return 0;
} 