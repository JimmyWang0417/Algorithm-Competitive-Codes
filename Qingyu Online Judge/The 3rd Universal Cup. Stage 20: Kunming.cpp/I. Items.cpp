#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 8e5 + 5;
constexpr int mod = 998244353;
constexpr inline ll quickpow(ll a, int b = mod - 2)
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
constexpr int inv3 = quickpow(3, mod - 2);
int limit, len, rk[N];
inline void init(int n)
{
	len = 0;
	limit = 1;
	while (limit < n)
	{
		limit <<= 1;
		++len;
	}
	for (int i = 0; i < limit; ++i)
		rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
}
struct poly
{
	vector<ll> dp;
	poly(int _n = 0)
	{
		dp.resize(_n);
	}
	inline int size()
	{
		return (int)dp.size();
	}
	inline void resize(int n)
	{
		dp.resize(n);
	}
	template <typename T>
	inline ll operator [](const T &x) const
	{
		return dp[x];
	}
	template <typename T>
	inline ll &operator [](const T &x)
	{
		return dp[x];
	}
	inline void NTT()
	{
		for (int i = 0; i < limit; ++i)
			if (i < rk[i])
				swap(dp[i], dp[rk[i]]);
		for (int mid = 1; mid < limit; mid <<= 1)
		{
			ll gn = quickpow(3, (mod - 1) / (mid << 1));
			for (int i = 0; i < limit; i += mid << 1)
			{
				ll g = 1;
				for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
				{
					ll x = dp[i + j], y = dp[i + j + mid] * g % mod;
					dp[i + j] = (x + y) % mod;
					dp[i + j + mid] = (x - y) % mod;
				}
			}
		}
	}
	inline void INTT()
	{
		for (int i = 0; i < limit; ++i)
			if (i < rk[i])
				swap(dp[i], dp[rk[i]]);
		for (int mid = 1; mid < limit; mid <<= 1)
		{
			ll gn = quickpow(inv3, (mod - 1) / (mid << 1));
			for (int i = 0; i < limit; i += mid << 1)
			{
				ll g = 1;
				for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
				{
					ll x = dp[i + j], y = dp[i + j + mid] * g % mod;
					dp[i + j] = (x + y) % mod;
					dp[i + j + mid] = (x - y) % mod;
				}
			}
		}
		ll inv = quickpow(limit);
		for (int i = 0; i < limit; ++i)
			(dp[i] *= inv) %= mod;
	}
	inline friend auto operator*(poly lhs, poly rhs)
	{
		int up = lhs.size() + rhs.size() - 1;
		init(up);
		poly res(limit);
		lhs.resize(limit), rhs.resize(limit);
		lhs.NTT(), rhs.NTT();
		for (int i = 0; i < limit; ++i)
			res[i] = lhs[i] * rhs[i] % mod;
		res.INTT();
		res.resize(up);
		return res;
	}
	inline void update(int x)
	{
		dp.erase(dp.begin(), dp.begin() + x);
		dp.erase(dp.end() - x, dp.end());
	}
	inline void print()
	{
		for (auto x : dp)
			cout << (x + mod) % mod << ' ';
		cout << '\n';
	}
};
inline void _main()
{
	int n;
	ll m;
	cin >> n >> m;
	poly res(2 * n + 1), f(2 * n + 1);
	for (int i = 0; i < n; ++i)
	{
		int x;
		cin >> x;
		f[x + n - m / n] = 1;
	}
	res[n] = 1;
	for (int i = 0; (1 << i) <= n; ++i)
	{
		if ((n >> i) & 1)
		{
			res = res * f;
			res.update(n);
		}
		f = f * f;
		f.update(n);
	}
	if (res[m % n + n])
		cout << "Yes\n";
	else
		cout << "No\n";
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