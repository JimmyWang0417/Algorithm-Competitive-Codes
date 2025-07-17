#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5e4 + 5;
typedef long long ll;
int n, m;
int a[N], b[N];
inline void _main()
{
	cin >> n >> m;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int i = 0; i < m; ++i)
		cin >> b[i];
	rotate(a, find(a, a + n, b[0]), a + n);
	if (equal(b, b + m, a))
	{
		cout << "1\n";
		return;
	}
	reverse(a, a + n);
	rotate(a, find(a, a + n, b[0]), a + n);
	if (equal(b, b + m, a))
	{
		cout << "1\n";
		return;
	}
	cout << "0\n";
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