#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 8e5 + 5;
constexpr int mod = 998244353;
inline void _main()
{
	string s;
	cin >> s;
	int cnt0 = 0, cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < (int)s.length(); ++i)
		if (s[i] == '2')
			++cnt2;
		else if ((s[i] == '1') ^ (i & 1))
			++cnt1;
		else
			++cnt0;
	int ans = INT_MAX;
	for (int i = 0; i <= cnt2; ++i)
		ans = min(ans, abs((cnt0 + i) - (cnt1 + cnt2 - i)));
	cout << ans << '\n';
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