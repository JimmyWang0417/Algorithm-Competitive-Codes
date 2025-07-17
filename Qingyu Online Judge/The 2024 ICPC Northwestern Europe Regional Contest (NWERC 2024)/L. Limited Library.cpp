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
int n, m, x, y;
int a[N], b[N];
inline void _main()
{
	cin >> n >> m >> x >> y;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	for (int i = 1; i <= m; ++i)
		cin >> b[i];
	sort(a + 1, a + 1 + n);
	sort(b + 1, b + 1 + m);
	auto check = [&](int mid)->int {
		vector<int> cnt(n + 5);
		for (int i = 1; i <= n; i++) {
			if (i <= mid) cnt[i] = y;
			else cnt[i] = x;
		}
		for (int i = 1, j = 1; i <= m; i++) {
			while (j <= n && (!cnt[j] || a[j] < b[i])) j++;
			if (j == n + 1) return false;
			cnt[j]--;
		}
		return true;
	};
	
	if (!check(0)) {
		cout << "impossible\n";
		return ;
	}
	
	int l = 0, r = n;
	while (l <= r) {
		int mid = l + r >> 1;
		if (check(mid)) 
			l = mid + 1;
		else r = mid - 1;
	}
	cout << r << '\n';
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