#include <bits/stdc++.h>
using namespace std;
constexpr int N = 50 * 100000 + 5;
typedef long long ll;
int n;
ll m;
inline void _main()
{
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
	{
		ll x;
		cin >> x;
		if (m <= 0 || (x - 1) >= (m - 1) / (i + 1) + 1)
		{
			cout << i << '\n';
			return;
		}
		m -= x;
	}
	cout << n << '\n';
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