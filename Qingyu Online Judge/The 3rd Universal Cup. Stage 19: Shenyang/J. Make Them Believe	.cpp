#include <bits/stdc++.h>
using namespace std;
pair<int, string> a[8];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	for (int i = 0; i < 8; ++i)
		cin >> a[i].second >> a[i].first;
	sort(a, a + 4);
	sort(a + 4, a + 8);
	if (a[3].first > a[7].first)
		cout << a[3].second << " beats " << a[7].second << '\n';
	else
		cout << a[7].second << " beats " << a[3].second << '\n';
	return 0;
}