#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
constexpr int inv2 = (mod + 1) / 2;
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
ll power[N], invpower[N];
ll fac[N], ifac[N];
inline void init(int n)
{
	power[0] = invpower[0] = 1;
	for (int i = 1; i <= n; ++i)
	{
		power[i] = power[i - 1] * 2 % mod;
		invpower[i] = invpower[i - 1] * inv2 % mod;
	}
	fac[0] = 1;
	for (int i = 1; i <= n; ++i)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = quickpow(fac[n], mod - 2);
	for (int i = n; i >= 1; --i)
		ifac[i - 1] = ifac[i] * i % mod;
}
inline ll C(int _n, int _m)
{
	if (_m < 0 || _n < _m)
		return 0;
	return fac[_n] * ifac[_m] % mod * ifac[_n - _m] % mod;
}
int n;
ll dp[N];
ll answer[N];
inline void _main()
{
	cin >> n;
	init(2 * n);
	dp[0] = power[n];
	for (int i = 0; i <= 2 * n - 2; ++i)
	{
		(dp[i] -= C(2 * n, i)) %= mod;
		(dp[i + 1] += dp[i] * 2) %= mod;
		(dp[i + 2] += dp[i]) %= mod;
		answer[i] = dp[i] % mod;
	}
	for (int i = 2; i <= n; ++i)
		(answer[i] += 2 * C(n, i)) %= mod;
	answer[1] = 0;
	for (int i = 0; i <= n; ++i)
		(answer[1] += power[i]) %= mod;
	for (int i = 1; i <= 2 * n - 2; ++i)
		cout << (answer[i] + mod) % mod << ' ';
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