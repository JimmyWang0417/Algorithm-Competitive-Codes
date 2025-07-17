#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = (1 << 17) + 5;
int n, a[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 0; i < (1 << n); ++i)
		cin >> a[i];
	sort(a, a + (1 << n), [](int x, int y) {
		return x > y; });
	ll res = a[0];
	for (int i = n - 1; i >= 0; --i)
	{
		ll sum = 0;
		for (int j = 0; j < (1 << i); ++j)
			sum += a[(1 << i) | j];
		res += max(sum, 0ll);
	}
	cout << res << '\n';
	return 0;
}