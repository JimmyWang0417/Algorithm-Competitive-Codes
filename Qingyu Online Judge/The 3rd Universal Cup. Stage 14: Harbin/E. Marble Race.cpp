#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
constexpr int N = 1e5 + 5;
constexpr int mod = 1e9 + 7;
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
int n, m;
int a[N], b[N];
pair<int, int> p[N * 10];
int tot;
int dp[N];
ll buf[2][N];
int cnt[N];
ll inv[N];
inline void work()
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	for (int i = 1; i <= m; ++i)
		cin >> b[i];
	inv[1] = 1;
	for (int i = 2; i <= n; ++i)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			p[++tot] = make_pair(i, j);
	sort(p + 1, p + 1 + tot, [](pair<int, int> x, pair<int, int> y) {
	return (ll)a[x.first] * b[y.second] > (ll)a[y.first] * b[x.second]; });
	auto f = buf[0], g = buf[1];
	ll ans = 0;
	f[0] = 1;
	for (int i = 1; i <= m; ++i)
		(f[0] *= (n - cnt[i])) %= mod;
	for (int T = 1; T <= tot; ++T)
	{
		int u = p[T].first, v = p[T].second;
		int limit = m / 2;
		swap(f, g);
		f[0] = g[0] * inv[n - cnt[v]] % mod;
		for (int j = 1; j <= limit; ++j)
			f[j] = (g[j] - f[j - 1] * cnt[v]) % mod * inv[n - cnt[v]] % mod;
//		for (int j = 0; j <= limit; ++j)
//			cout << f[j] << ' ';
//		cout << '\n';
//		printf("%d %d %lld\n", -a[p[T].first], b[p[T].second], f[limit]);
		(ans += (-a[p[T].first]) * quickpow(b[p[T].second], mod - 2) % mod * f[limit]) %= mod;
		++cnt[v];
		swap(f, g);
		for (int j = 0; j <= limit; ++j)
		{
			f[j] = g[j] * (n - cnt[v]);
			if (j)
				f[j] += g[j - 1] * cnt[v];
			f[j] %= mod;
		}
	}
	cout << (ans + mod) % mod * quickpow(quickpow(n, m), mod - 2) % mod << '\n';
}
signed main()
{
//	freopen("project.in", "r", stdin);
//	freopen("project.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T = 1;
	while (T--)
		work();
	return 0;
}