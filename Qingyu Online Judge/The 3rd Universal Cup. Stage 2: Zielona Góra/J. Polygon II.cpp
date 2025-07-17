#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1005;
constexpr int mod = 1e9 + 7;
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
int n, a[N];
ll power[N];
vector<ll> f, g;
ll fac[N * 50], ifac[N * 50];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	ll times = 1;
	for (int i = 1; i <= n; ++i)
	{
		int x;
		cin >> x;
		++a[x];
		(times *= (1ll << x) % mod) %= mod;
	}
	fac[0] = 1;
	for (int i = 1; i <= 50 * n; ++i)
		fac[i] = fac[i - 1] * i % mod;
	ifac[50 * n] = quickpow(fac[50 * n], mod - 2);
	for (int i = 50 * n; i >= 1; --i)
		ifac[i - 1] = ifac[i] * i % mod;
	auto C = [](int _x, int _y)
	{
		return fac[_x] * ifac[_y] % mod * ifac[_x - _y] % mod;
	};
	power[0] = 1;
	for (int i = 1; i <= n; ++i)
		power[i] = quickpow(i, n);
	f.resize(n + 1);
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < i; ++j)
			if (j & 1)
				(f[i - 1] -= C(n, j) * power[i - j] % mod * ifac[n]) %= mod;
			else
				(f[i - 1] += C(n, j) * power[i - j] % mod * ifac[n]) %= mod;
	for (int i = n - 1; i >= 1; --i)
		(f[i] -= f[i - 1]) %= mod;
	ll ans = 0;
	for (int i = 0; i <= 50; ++i)
	{
		(ans += f[0] * a[i]) %= mod;
		swap(f, g);
		int c = 0;
		for (int j = i + 1; j <= 50; ++j)
			c += a[j];
		f.resize((g.size() - 1 + c) / 2 + 1);
		fill(f.begin(), f.end(), 0);
		for (int j = 0; j < (int)g.size(); ++j)
			for (int k = 0; k <= c; ++k)
				(f[(j + k) / 2] += g[j] * C(c, k)) %= mod;
	}
	(ans *= quickpow(times, mod - 2)) %= mod;
	cout << (1 - ans + mod) % mod << '\n';
	return 0;
}