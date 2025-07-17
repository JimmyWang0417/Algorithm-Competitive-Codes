#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5 + 5;
typedef long long ll;
int prime[N], tot;
bool vis[N];
inline void init(int n)
{
	for (int i = 2; i <= n; ++i)
	{
		if (!vis[i])
			prime[++tot] = i;
		for (int j = 1; j <= tot; ++j)
		{
			if (i * prime[j] > n)
				break;
			vis[i * prime[j]] = true;
			if (i % prime[j] == 0)
				break;
		}
	}
}
int mod;
int block;
int id1[N], id2[N];
ll p[N];
int ptot;
ll dp[N];
ll n;
inline ll solve(ll x, int y, int z)
{
	if (x <= prime[y])
		return 0;
	int k = (x <= block) ? id1[x] : id2[n / x];
	if (z == 1)
	{
		ll res = dp[k] - y;
		for (int i = y + 1; i <= tot && (ll)prime[i] * prime[i] <= x; ++i)
		{
			ll pe = (ll)prime[i] * prime[i];
			for (int j = 2; pe <= x; ++j, pe *= prime[i])
				res++;
		}
		return res;
	}
	ll res = 0;
	for (int i = y + 1; i <= tot && (ll)prime[i] * prime[i] <= x; ++i)
	{
		ll pe = prime[i];
		for (int j = 1; pe <= x; ++j, pe *= prime[i])
			res += solve(x / pe, i, z - 1);
	}
	return res;
}
inline ll quickpow(ll a, ll b)
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
inline void _main()
{
	cin >> n >> mod;
	block = (int)round(sqrt(n));
	init(block);
	for (ll i = 1, j; i <= n; i = j + 1)
	{
		j = n / (n / i);
		p[++ptot] = n / i;
		dp[ptot] = n / i - 1;
		if (n / i <= block)
			id1[n / i] = ptot;
		else
			id2[n / (n / i)] = ptot;
	}
	for (int i = 1; i <= tot; ++i)
		for (int j = 1; j <= ptot && (ll)prime[i] * prime[i] <= p[j]; ++j)
		{
			int k = (p[j] / prime[i] <= block ? id1[p[j] / prime[i]] : id2[n / (p[j] / prime[i])]);
			dp[j] -= dp[k] - (i - 1);
		}
	ll res = 1;
	for (int i = 2; i <= 10; ++i)
		(res *= quickpow(i, solve(n, 0, i))) %= mod;
	cout << res << '\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int test = 1;
	while (test--)
		_main();
	return 0;
}