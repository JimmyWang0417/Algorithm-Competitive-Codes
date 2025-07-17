#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
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
int n, m;
ll power[N], invpower[N];
ll dp[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	ll invm = quickpow(m, mod - 2);
	power[0] = invpower[0] = 1;
	for (int i = 1; i <= n; ++i)
	{
		power[i] = power[i - 1] * m % mod;
		invpower[i] = invpower[i - 1] * invm % mod;
	}
	ll sum = 0, ans = 0;
	for (int i = 1; i * 2 < n; ++i)
	{
		if (i % 2 == 0)
			(sum += dp[i / 2] * invpower[i]) %= mod;
		dp[i] = (1 - sum) * power[i] % mod;
		(ans += dp[i] * power[n - 2 * i]) %= mod;
	}
	cout << (ans + mod) % mod << '\n';
	return 0;
}