#include <bits/stdc++.h>
using namespace std;
constexpr int N = 105;
int n;
char str[N];
int p[N];
vector<int> g[N];
bool sit[N], is[N]; 
signed main()
{
	scanf("%d", &n); 

	auto check = [](int mid, int T)
	{
		int hh = mid / 60, mm = mid % 60;
		printf("at %d%d:%d%d check %d\n", hh / 10, hh % 10, mm / 10, mm % 10, T);
		fflush(stdout);
		scanf("%s", str);
		return str[1] == 'w';
	};
    for (int i = 1; i <= n; i++)
        sit[i] = check(0, i);

    int now = 0;

    for (int i = 1, bed = 47; bed; i++, bed--) {
        now += bed;

        if (now >= 720) {
            for (int j = 1; j <= n; j++)
                if (!is[j]) {
                    is[j] = 1;
                    g[i].push_back(j);
                }

            break;
        }

        for (int j = 1; j <= n; j++) {
            if (is[j])
                continue;

            if (check(now, j) != sit[j]) {
                is[j] = 1;
                g[i].push_back(j);
            }
        }
    }

    now = 720;

    for (int i = 1, bed = 47; bed; i++, bed--) {
        for (int j = 0; j <= bed; j++) {
            if (now + j >= 1440) {
                for (int k = 1; k <= n; k++)
                    if (is[k]) {
                        is[k] = 0;
                        p[k] = sit[k] ? 1440 : 0;
                    }

                break;
            }

            for (int u : g[i]) {
                if (!is[u])
                    continue;

                if (check(now + j, u) == sit[u]) {
                    is[u] = 0;
                    p[u] = now + j;
                }
            }
        }

        now += bed;
    }

	printf("answer\n");

    for (int i = 1; i <= n; i++) {
    	if (sit[i])
    		p[i] = (p[i] + 720) % 1440;
		int hh = p[i] / 60, mm = p[i] % 60;
		printf("%d%d:%d%d\n", hh / 10, hh % 10, mm / 10, mm % 10);
	}
}