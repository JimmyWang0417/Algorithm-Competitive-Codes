#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 2e6 + 5;
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
int n, a[N];
ll fac[N], ifac[N];
inline void init(int m)
{
	fac[0] = 1;
	for (int i = 1; i <= m; ++i)
		fac[i] = fac[i - 1] * i % mod;
	ifac[m] = quickpow(fac[m], mod - 2);
	for (int i = m; i >= 1; --i)
		ifac[i - 1] = ifac[i] * i % mod;
}
inline void _main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	init(2 * n);
	for (int i = 1; i < n; ++i)
		if (a[i] == 1)
		{
			cout << "0\n";
			return;
		}
	auto C = [](int _x, int _y) -> ll
	{
		if (_y < 0 || _x < _y)
			return 0;
		return fac[_x] * ifac[_y] % mod * ifac[_x - _y] % mod;
	};
	auto calc = [C](int _x, int _y)
	{
		return (C(_x + _y, _x) - C(_x + _y, _y - 2)) % mod;
	};
	if (a[n] == 1)
	{
		--n;
		ll res = 1;
		for (int i = n, j = n, k = n; i >= 1; i = k)
		{
			j = i;
			while (j >= 1 && a[j] == 2)
				--j;
			k = j;
			while (k >= 1 && a[k] == 3)
				--k;
			int cnt3 = j - k; 
			(res *= calc(cnt3, cnt3)) %= mod;
		}
		cout << (res + mod) % mod << '\n';
	}
	else
	{
		ll res = 1;
		int end2 = 0, end3 = 0;
		while (end2 <= n && a[n - end2] == 2)
			++end2;
		while (end2 + end3 <= n && a[n - end2 - end3] == 3)
			++end3;
		for (int i = n - end2 - end3, j = n, k = n; i >= 1; i = k)
		{
			j = i;
			while (j >= 1 && a[j] == 2)
				--j;
			k = j;
			while (k >= 1 && a[k] == 3)
				--k;
			int cnt3 = j - k; 
			(res *= calc(cnt3, cnt3)) %= mod;
		}
		ll ans = ((calc(end3, end3) * end2) + calc(end3 + end2, end3)) % mod * res % mod;
		cout << (ans + mod) % mod << '\n';
	}
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