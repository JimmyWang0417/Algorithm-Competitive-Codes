#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e5 + 5;
int n, a[N];
inline void _main()
{
	cin >> n;
	ll sum = 0;
	int maxx = 0;
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		sum += a[i];
		maxx = max(maxx, a[i]);
	}
	if (sum && sum - maxx < n)
		cout << "Donkey\n";
	else
		cout << "Puss in Boots\n";
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