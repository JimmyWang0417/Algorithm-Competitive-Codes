#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
typedef long double ld;
constexpr int N = 2e5 + 5;
constexpr int mod1 = 1e9 + 7;
constexpr int mod2 = 1e9 + 9;
const long double log_10 = log(10.0);
const long double log_5r = log(sqrt(5));
template <int mod>
struct matrix
{
	ll g[2][2];
	matrix() { memset(g, 0, sizeof(g)); }
	inline matrix operator*(const matrix &rhs) const
	{
		matrix res;
		for (int i = 0; i < 2; ++i)
			for (int k = 0; k < 2; ++k)
				for (int j = 0; j < 2; ++j)
					(res.g[i][j] += g[i][k] * rhs.g[k][j]) %= mod;
		return res;
	}
	inline matrix operator^(int power) const
	{
		matrix res, _a = (*this);
		for (int i = 0; i < 2; ++i)
			res.g[i][i] = 1;
		while (power)
		{
			if (power & 1)
				res = res * _a;
			_a = _a * _a;
			power >>= 1;
		}
		return res;
	}
};
int n;
string a[N];
matrix<mod1> b;
matrix<mod2> c;
__gnu_pbds::gp_hash_table<ll, int> mp;
__gnu_pbds::gp_hash_table<ll, bool> vis;
inline void work()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	sort(a + 1, a + 1 + n, [](const string &x, const string &y) {
	return x.length() == y.length() ? x < y : x.length() < y.length(); });
//	for (int i = 1; i <= n; ++i)
//		cout << a[i] << ' ';
//	cout << endl;
	b.g[0][0] = 0, b.g[0][1] = 1;
	b.g[1][0] = 1, b.g[1][1] = 1;
	c.g[0][0] = 0, c.g[0][1] = 1;
	c.g[1][0] = 1, c.g[1][1] = 1;
	ll ans = 0;
	for (int i = 1; i <= n; ++i)
	{
		ld res = 0;
		int v1 = 0, v2 = 0;
		for (int j = 0; j < min(30, (int)a[i].length()); ++j)
			res = res * 10 + a[i][j] - '0';
		for (auto j : a[i])
		{
			v1 = ((ll)v1 * 10 + j - '0') % mod1;
			v2 = ((ll)v2 * 10 + j - '0') % mod2;
		}
//		printf("%d %d %d:\n", i, v1, v2);
		int x = (int)((log(res) + log_10 * (a[i].length() - min(30, (int)a[i].length())) + log_5r) / log((1 + sqrt(5)) / 2));
//		cout << x << '\n';
		matrix<mod1> res1;
		matrix<mod2> res2;
		for (int j = max(x - 10, 0); j <= x + 10; ++j)
		{
			if (j == max(x - 10, 0))
			{
				res1 = (b ^ j);
				res2 = (c ^ j);
			}
			else
			{
				res1 = res1 * b;
				res2 = res2 * c;
			}
			int u1 = (int)res1.g[0][1], u2 = (int)res2.g[0][1];
			ll u = (ll)(u1 - v1+ mod1) % mod1 * mod2 + (u2 - v2 + mod2) % mod2;
//			printf("%d %d %d %d %d %lld\n", j, u1, u2, (u1 - v1+ mod1) % mod1,  (u2 - v2 + mod2) % mod2, u);
			if (vis[u])
				continue;
			vis[u] = true;
			ans += mp[u];
		}
		++mp[(ll)v1 * mod2 + v2];
		vis.clear();
	}
	cout << ans << '\n';
	mp.clear();
}
signed main()
{
//	freopen("project.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T = 1;
	while (T--)
		work();
	return 0;
}