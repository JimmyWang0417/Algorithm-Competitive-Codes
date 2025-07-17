#include <bits/stdc++.h>
using namespace std;
inline int get(int x)
{
	int d = 0;
	while (x)
	{
		d = max(d, x % 10);
		x /= 10;
	}
	return d;
}
inline void work()
{
	int l1, r1, l2, r2;
	cin >> l1 >> r1 >> l2 >> r2;
	r1 = min(r1, l1 + 9);
	r2 = min(r2, l2 + 9);
	int maxx = 0;
	for (int i = l1; i <= r1; ++i)
		for (int j = l2; j <= r2; ++j)
			maxx = max(maxx, get(i + j));
	cout << maxx << '\n';
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