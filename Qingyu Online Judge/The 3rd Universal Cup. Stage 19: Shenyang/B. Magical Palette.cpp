#include <bits/stdc++.h>
using namespace std;
int n, m;
inline void _main()
{
	cin >> n >> m;
	if (__gcd(n, m) > 1)
		cout << "No\n";
	else
	{
		cout << "Yes\n";
		for (int i = 0; i < n; ++i)
			cout << (i * m + 1) % (n * m) << ' ';
		cout << '\n';
		for (int i = 0; i < m; ++i)
			cout << (n * i + 1) % (n * m) << ' ';
		cout << '\n';
	}
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