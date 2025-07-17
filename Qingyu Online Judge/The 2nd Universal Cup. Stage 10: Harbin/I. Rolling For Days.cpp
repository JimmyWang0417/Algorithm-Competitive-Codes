#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1005;
constexpr int M = (1 << 12) + 5;
constexpr int mod = 998244353;
typedef long long ll;
ll fac[N], ifac[N];
inline ll quickpow(ll a, int b = mod - 2)
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
int a[N], b[N], Log[M], suma[M], sumb[M];
ll f[M][N], g[M][N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < m; ++i)
		cin >> a[i];
	int all = 0;
	for (int i = 0; i < m; ++i)
	{
		cin >> b[i];
		if (!b[i])
			all |= 1 << i;
	}
	for (int i = 0; i < m; ++i)
	{
		Log[1 << i] = i;
		for (int j = 0; j < (1 << i); ++j)
		{
			suma[1 << i | j] = a[i] + suma[j];
			sumb[1 << i | j] = b[i] + sumb[j];
		}
	}
	fac[0] = 1;
	for (int i = 1; i <= n; ++i)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = quickpow(fac[n]);
	for (int i = n; i >= 1; --i)
		ifac[i - 1] = ifac[i] * i % mod;
	auto C = [](int _n, int _m) -> ll
	{
		if (_m < 0 || _n < _m)
			return 0;
		return fac[_n] * ifac[_m] % mod * ifac[_n - _m] % mod;
	};
	auto inv = [](int x) -> ll
	{
		if (x <= 0)
			return 0;
		return ifac[x] * fac[x - 1] % mod;
	};
	auto lowbit = [](int x)
	{
		return x & (-x);
	};
	f[all][0] = 0, g[all][0] = 1;
	for (int S = 1; S < (1 << m); ++S)
	{
		if ((S & all) != all)
			continue;
		for (int _S = S; _S; _S ^= lowbit(_S))
		{
			int x = Log[lowbit(_S)];
			ll timesb = 1;
			for (int i = 1; i <= b[x]; ++i)
				(timesb *= a[x] - i + 1) %= mod;
			ll sumf = 0, sumg = 0, sumgsum = 0;
			for (int i = 1; i <= sumb[(1 << m) - 1]; ++i)
			{
				auto add = inv(n - i + 1 - suma[S ^ (1 << x)] + sumb[S ^ (1 << x)]);
				(sumf += f[S ^ (1 << x)][i - 1]) %= mod;
				(sumg += g[S ^ (1 << x)][i - 1]) %= mod;
				(sumgsum += (n - i + 1) * add % mod * sumg) %= mod;
				(sumf *= add) %= mod;
				(sumg *= add) %= mod;
				(sumgsum *= add) %= mod;
				auto add2 = C(i - 1 - sumb[S ^ (1 << x)], b[x] - 1) * timesb % mod;
				(f[S][i] += (sumf + sumgsum) * add2) %= mod;
				(g[S][i] += sumg * add2) %= mod;
			}
		}
//		for (int i = sumb[S]; i <= sumb[(1 << m) - 1]; ++i)
//		{
//			for (int _S = S; _S; _S ^= lowbit(_S))
//			{
//				int x = Log[lowbit(_S)];
//				ll times = C(i - 1 - sumb[S ^ (1 << x)], b[x] - 1), sum = 0;
//				for (int j = 1; j <= b[x]; ++j)
//					(times *= a[x] - j + 1) %= mod;
//				for (int j = i - 1; j >= sumb[S ^ (1 << x)]; --j)
//				{
//					(sum += (n - j) * inv(n - j - suma[S ^ (1 << x)] + sumb[S ^ (1 << x)])) %= mod;
//					(times *= inv(n - j - suma[S ^ (1 << x)] + sumb[S ^ (1 << x)])) %= mod;
//
//					(f[S][i] += (f[S ^ (1 << x)][j] + g[S ^ (1 << x)][j] * sum) % mod * times) %= mod;
//					(g[S][i] += g[S ^ (1 << x)][j] * times) %= mod;
//				}
//			}
//		}
	}
	cout << f[(1 << m) - 1][sumb[(1 << m) - 1]] << '\n';
	return 0;
}