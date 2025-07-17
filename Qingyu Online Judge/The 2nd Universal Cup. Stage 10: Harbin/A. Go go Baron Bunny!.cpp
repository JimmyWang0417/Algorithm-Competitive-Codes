#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;
typedef long long LL;
#define N 2000000 + 5
#define Mod 998244353

int sz, ans, Fac[N], Inv[N], Cnt[N];
LL n, k, t;

void Prepare()
{
    for (sz = 1; LL(sz) * (sz + 1) / 2 < n; sz++)
        ;
    Fac[0] = Inv[0] = Inv[1] = 1;
    for (int i = 1; i <= sz; i++)
        Fac[i] = LL(i) * Fac[i - 1] % Mod;
    for (int i = 2; i <= sz; i++)
        Inv[i] = Mod - LL(Mod / i) * Inv[Mod % i] % Mod;
    for (int i = 2; i <= sz; i++)
        Inv[i] = LL(Inv[i - 1]) * Inv[i] % Mod;
}

inline int Inc(int u, int v)
{
    return u >= Mod - v ? u - (Mod - v) : u + v;
}

inline int C(int u, int v)
{
    if (u < 0 || v < 0 || u < v)
        return 0;
    return LL(Fac[u]) * Inv[v] % Mod * Inv[u - v] % Mod;
}

inline int S(int u, int v)
{
    if (u == 0 && v == 0)
        return 1;
    return C(u - 1, v - 1);
}

int Calc(int len, int one_cnt, int pre_div, int last_val)
{
    for (int comb_cnt = 0; comb_cnt <= one_cnt; comb_cnt++)
    {
        int ret_0_cnt = len - one_cnt - comb_cnt;
        int tmp, acomb_cnt;
        if (last_val == 0)
        {
            // sum = one_cnt, cnt = comb_cnt, C(sum - 1, cnt - 1)
            tmp = LL(C(ret_0_cnt + comb_cnt, comb_cnt)) * S(one_cnt, comb_cnt) % Mod;
            acomb_cnt = comb_cnt * pre_div;
            Cnt[acomb_cnt] = Inc(Cnt[acomb_cnt], tmp);
        }
        else
        {
            // sum = one_cnt, cnt = comb_cnt + 1, C(sum - 1, cnt - 1)
            // first_val == 0
            tmp = LL(C(ret_0_cnt + comb_cnt - 1, comb_cnt)) * S(one_cnt, comb_cnt + 1) % Mod;
            acomb_cnt = comb_cnt * pre_div + pre_div - 1;
            Cnt[acomb_cnt] = Inc(Cnt[acomb_cnt], tmp);
            // first_val == 1
            tmp = LL(C(ret_0_cnt + comb_cnt - 1, comb_cnt - 1)) * S(one_cnt, comb_cnt + 1) % Mod;
            acomb_cnt = comb_cnt * pre_div;
            Cnt[acomb_cnt] = Inc(Cnt[acomb_cnt], tmp);
        }
    }
    int ret = 0;
    for (int comb_cnt = 0, fac = Fac[len * pre_div - last_val]; comb_cnt <= one_cnt * pre_div; comb_cnt++, fac = LL(fac) * Inv[2] % Mod)
        ret = (LL(Cnt[comb_cnt]) * fac + ret) % Mod;
    return ret;
}

int main()
{
    scanf("%lld%lld%lld", &n, &k, &t);
    Prepare();
    t = __gcd(LL(sz), t);
    int one_cnt = LL(sz) * (sz + 1) / 2 - n;
    int div = sz / t;
    if (one_cnt % div == 0)
    {
        if (k == sz || k == sz - 1)
            ans = Calc(t, one_cnt / div, div, sz - k);
        else
            ans = 0;
    }
    else
        ans = 0;
    printf("%d\n", ans);
    return 0;
}