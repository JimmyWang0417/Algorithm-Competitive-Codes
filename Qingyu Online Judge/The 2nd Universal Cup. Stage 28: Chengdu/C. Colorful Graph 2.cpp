#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5 + 5;
int n, m, a[N];
bool b[N];
inline void work()
{
	cin >> n >> m;
	for (int i = 2; i <= n; ++i)
		a[i] = i - 1;
	for (int i = 1; i <= m; ++i)
	{
		int x, y;
		cin >> x >> y;
		++x, ++y;
		if (x > y)
			swap(x, y);
		a[y] = min(a[y], x);
	}
	for (int i = 1; i <= n; ++i)
		b[i] = b[a[i]] ^ 1;
	for (int i = 1; i <= n; ++i)
		putchar(b[i] ? 'R' : 'B');
	putchar('\n');
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--)
		work();
	return 0;
}