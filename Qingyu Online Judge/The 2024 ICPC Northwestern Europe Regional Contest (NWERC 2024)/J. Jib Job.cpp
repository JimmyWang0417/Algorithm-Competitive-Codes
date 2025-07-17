#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 6e6 + 5;
inline ll quickpow(ll a, ll b, int p) 
{
	ll res = 1;
	while (b) 
	{
		if (b & 1) 
			res = res * a % p;
		a = a * a % p; b >>= 1;
	}
	return res;
}
int n;
tuple<int, int, int> a[N];
inline void _main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		auto &[x, y, h] = a[i];
		cin >> x >> y >> h;
	}
	for (int i = 1; i <= n; ++i)
	{
		auto [x, y, res] = a[i];
		for (int j = 1; j <= n; ++j)
		{
			if (i == j)
				continue;
			if (get<2> (a[j]) < get<2>(a[i]))
				continue;
			auto [l, r, qwq] = a[j];
//			printf("%d %d %d\n", i, j, (int)(sqrt((double)(x - l) * (x - l) + (double)(y - r) * (y - r)) - 1e-6));
			res = min(res, (int)(sqrt((double)(x - l) * (x - l) + (double)(y - r) * (y - r))));
		}
		cout << res << '\n';
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