#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5e5 + 5;
typedef long double ld;
int n;
struct node
{
	int x, y;
	inline bool operator<(const node &rhs) const
	{
		return x < rhs.x;
	}
} a[N];
inline void _main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i].x >> a[i].y;
	sort(a + 1, a + 1 + n);
	bool flag = false;
	for (int i = 1; i < n; ++i)
	{
		if (a[i].x == a[i + 1].x)
		{
			flag = true;
			break;
		}
	}
	long double res = 0;
	if (flag)
	{
		for (int i = 1; i < n; ++i)
		{
			if (a[i].x == a[i + 1].x)
				continue;
			if ((a[i].x + a[i + 1].x) % 2)
				cout << "? " << a[i].x + a[i + 1].x << " 2" << endl;
			else
				cout << "? " << (a[i].x + a[i + 1].x) / 2 << " 1" << endl;
			long double p, q;
			cin >> p >> q;
			res += (long double)(a[i + 1].x - a[i].x) * p / q;
		}
	}
	else
	{
		for (int i = 2; i < n; ++i)
		{
			cout << "? " << a[i].x << " 1" << endl;
			long double p, q;
			cin >> p >> q;
			res += (long double)(a[i + 1].x - a[i - 1].x) * p / q / 2;
		}
	}
	long long ans = roundl(res * 2);
	if (ans % 2 == 0)
		cout << "! " << ans / 2 << ' ' << 1 << endl;
	else
		cout << "! " << ans << ' ' << 2 << endl;
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