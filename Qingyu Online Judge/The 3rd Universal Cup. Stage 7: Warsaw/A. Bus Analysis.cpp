#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define int ll
using namespace std;
typedef long long ll;
constexpr int N = 1005, M = 1e4 + 5;
constexpr int mod = 1e9 + 7;
int n, a[N];
int power[N];
tuple<int, int, int> p[M];
int mp[83][83][83];
int tot;
int buf[2][M];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	for (int i = 0; i <= 75; ++i)
		for (int j = i + 20; j <= 75; ++j)
			for (int k = j + 20; k <= 75; ++k)
				p[mp[i][j][k] = tot++] = make_tuple(i, j, k);
	auto f = buf[0], g = buf[1];
	f[0] = 1;
	ll ans = 0;
	power[0] = 1;
	for (int i = 1; i <= n; ++i)
		power[i] = power[i - 1] * 2 % mod;
	for (int i = 1; i <= n; ++i)
	{
		swap(f, g);
		memset(f, 0, sizeof(buf[0]));
		for (int j = 0; j < tot; ++j)
		{
			if (!g[j])
				continue;
			int x = max(0ll, get<0>(p[j]) - a[i] + a[i - 1]), 
				y = max(0ll, get<1>(p[j]) - a[i] + a[i - 1]), 
				z = max(0ll, get<2>(p[j]) - a[i] + a[i - 1]);
			y = max(y, x + 20);
			z = max(z, y + 20);
			int r = max(z + 20, x + 75);
			(f[mp[x][y][z]] += g[j]) %= mod;
			if (!x)
			{
				(f[mp[y][z][r]] += g[j]) %= mod;
				(ans += (ll)g[j] * power[n - i]) %= mod;
			}
			else
				(f[mp[x][y][z]] += g[j]) %= mod;
		}
	}
	cout << ans * 2 % mod << '\n';
	return 0;
}