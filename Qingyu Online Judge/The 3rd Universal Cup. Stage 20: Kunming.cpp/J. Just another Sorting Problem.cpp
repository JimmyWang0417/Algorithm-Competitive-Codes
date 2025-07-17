#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
int n, a[N];
inline void _main()
{
	string s;
	cin >> n >> s;
	int res = 0;
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		res += (a[i] != i);
	}
	if (n == 2)
	{
		cout << "Alice" << '\n';
		return;
	}
	if (n == 3)
	{
		if (a[1] == 3 && a[2] == 1 && a[3] == 2 && s == "Bob")
		{
			cout << "Alice" << '\n';
			return;
		}
		if (a[1] == 2 && a[2] == 3 && a[3] == 1 && s == "Bob")
		{
			cout << "Alice" << '\n';
			return;
		}
	}
	if (res == 2 && s == "Alice")
	{
		cout << s << '\n';
		return;
	}
	cout << "Bob\n";
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