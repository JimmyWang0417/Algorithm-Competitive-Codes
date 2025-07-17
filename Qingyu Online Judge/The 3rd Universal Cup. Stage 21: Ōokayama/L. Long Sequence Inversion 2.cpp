#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N = 5e5 + 5;
constexpr int mod = 998244353;
auto lowbit = [](int x)
{
	return x & (-x);
};
struct BIT
{
	int n, c[N];
	inline void update(int pos, int val)
	{
		for (int i = pos + 1; i <= n; i += lowbit(i))
			c[i] += val;
	}
	inline int query(int pos)
	{
		int res = 0;
		for (int i = pos; i; i -= lowbit(i))
			res += c[i];
		return res;
	}
	inline void clear()
	{
		for (int i = 1; i <= n; ++i)
			c[i] = 0;
	}
} p, q;
int n, m;
int a[N];
ll power[N];
inline int calc()
{
	int res = 0;
	for (int i = 0; i < m; ++i)
	{
		int x;
		cin >> x;
		(res += i - q.query(x)) %= mod;
		q.update(x, 1);
	}
	q.clear();
	return res;
}
inline ll square(ll x)
{
	return (ll)x * (x - 1) / 2 % mod;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	power[0] = 1;
	for (int i = 1; i <= n; ++i)
		power[i] = power[i - 1] * m % mod;
	ll res = 0;
	p.n = n, q.n = m;
	for (int i = 0; i < n; ++i)
	{
		int c = p.query(a[i]);
		ll k = power[a[i] - c];
		int t = calc();
		ll s = (t * k + square(k) * square(m)) % mod;
		(res += s * power[c] % mod * power[c] % mod * power[n - a[i] - 1]) %= mod;
		p.update(a[i], 1);
	}
	cout << res << '\n';
	return 0;
}