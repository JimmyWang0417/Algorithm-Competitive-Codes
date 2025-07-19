#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <typename T>
inline void ckmax(T &x, T y)
{
	if (x < y)
		x = y;
}
template <typename T>
inline void ckmin(T &x, T y)
{
	if (x > y)
		x = y;
}
constexpr int N = 1e6 + 5;
int n, a[N], b[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	for (int i = 0; i < n; ++i)
		cin >> b[i];
	int ans = INT_MAX;
	for (int T = 0; T < 30; ++T)
	{
		int minn = INT_MAX, maxx = INT_MIN;
		for (int i = 0; i < n; ++i)
		{
			ckmin(minn, b[i] - (a[i] >> T));
			ckmax(maxx, b[i] - (a[i] >> T));
		}
		if (minn < 0 || maxx - minn > 1)
			continue;
		if (minn == maxx)
		{
			ckmin(ans, T + minn);
			continue;
		}
		int l = -1, r = INT_MAX;
		for (int i = 0; i < n; ++i)
		{
			int c = b[i] - (a[i] >> T) - minn;
			int d = ((1 << T) - 1) ^ (((1 << T) - 1) & a[i]);
			if (c)
				ckmax(l, d + 1);
			else
				ckmin(r, d);
		}
		if (l > r)
			continue;
		int res = T + minn;
		for (int i = 30; i >= 0; --i)
		{
			if(((l >> i) & 1) ^ (((r >> i) & 1)))
			{
				++res;
				break;
			}
			if ((r >> i) & 1)
				++res;
		}
		ckmin(ans, res);
	}
	cout << (ans == INT_MAX ? -1 : ans) << '\n';
	return 0;
}