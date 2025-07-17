#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 3e5 + 5;
int n, m;
int a[N], b[N];
int c[N];
auto lowbit = [](int x)
{
	return x & (-x);
};
inline void update(int pos)
{
	for (int i = pos; i; i -= lowbit(i))
		++c[i];
}
inline int query(int pos)
{
	int res = 0;
	for (int i = pos; i <= n; i += lowbit(i))
		res += c[i];
	return res;
}
inline void _main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		b[a[i]] = i;
	}
	int res = 0;
	for (int i = n - 1; i >= 1; --i)
		if (b[i] > b[i + 1])
		{
			res = i;
			break;
		}
	cout << res << ' ' << res << '\n';
	for (int i = res; i >= 1; --i)
	{
		cout << (query(b[i]) + b[i]) << ' ' << 1 << '\n';
		update(b[i]);
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