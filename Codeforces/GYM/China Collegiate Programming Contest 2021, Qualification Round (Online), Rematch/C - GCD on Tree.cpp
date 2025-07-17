/**
 *    name:     C. GCD on Tree
 *    author:   whitepaperdog (蒟蒻wjr)
 *    located:  Xuanwu District, Nanjing City, Jiangsu Province, China
 *    created:  2023.03.13 周一 09:48:43 (Asia/Shanghai)
 *    unicode:  UTF-8
 *    standard: c++23
 **/
#include <cstdio>
#include <vector>
typedef long long ll;
typedef unsigned long long ull;
#define lowbit(x) ((x) & (-(x)))

// #define FAST_IO

#if !defined(WIN32) && !defined(_WIN32)
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif
namespace IO
{
#ifdef FAST_IO
#ifndef FAST_IN
#define FAST_IN
#endif
#ifndef FAST_OUT
#define FAST_OUT
#endif
#endif

    namespace INPUT
    {
#ifdef FAST_IN
#ifndef FAST_OUT_BUFFER_SIZE
#define FAST_OUT_BUFFER_SIZE (1 << 21)
#endif
        char _buf[FAST_OUT_BUFFER_SIZE], *_now = _buf, *_end = _buf;
#undef getchar
#define getchar() (_now == _end && (_end = (_now = _buf) + fread(_buf, 1, FAST_OUT_BUFFER_SIZE, stdin), _now == _end) ? EOF : *_now++)
#else
#if !defined(WIN32) && !defined(_WIN32)
#define getchar getchar_unlocked
#endif
#endif
        inline void read(char &_x)
        {
            char _s = (char)getchar();
            while ((_s >= 0x0a && _s <= 0x0d) || (_s == 0x09) || (_s == 0x20))
                _s = (char)getchar();
            _x = _s;
        }
        inline int read(char *_x)
        {
            char _s = (char)getchar();
            int _len = 0;
            while ((_s >= 0x0a && _s <= 0x0d) || (_s == 0x09) || (_s == 0x20))
                _s = (char)getchar();
            while (!((_s >= 0x0a && _s <= 0x0d) || (_s == 0x09) || (_s == 0x20)) && _s != EOF)
            {
                _x[_len++] = _s;
                _s = (char)getchar();
            }
            _x[_len] = '\0';
            return _len;
        }
        template <typename _T>
        inline void read(_T &_x)
        {
            _x = 0;
            char _s = (char)getchar();
            bool _f = false;
            while (!(_s >= '0' && _s <= '9'))
            {
                if (_s == '-')
                    _f = true;
                _s = (char)getchar();
            }
            while (_s >= '0' && _s <= '9')
            {
                _x = (_x << 1) + (_x << 3) + (_s - '0');
                _s = (char)getchar();
            }
            if (_f)
                _x = -_x;
        }
        template <typename _T, typename... _G>
        inline void read(_T &_x, _G &..._y)
        {
            read(_x);
            read(_y...);
        }
#ifdef FAST_IN
#undef getchar
#if !defined(WIN32) && !defined(_WIN32)
#define getchar getchar_unlocked
#endif
#endif
    }
    namespace OUTPUT
    {
#ifdef FAST_OUT
#ifndef FAST_OUT_BUFFER_SIZE
#define FAST_OUT_BUFFER_SIZE (1 << 21)
#endif
        char _buf[FAST_OUT_BUFFER_SIZE], *_now = _buf;
        inline void flush()
        {
            fwrite(_buf, 1, _now - _buf, stdout), _now = _buf;
        }
#undef putchar
#define putchar(c) (_now - _buf == FAST_OUT_BUFFER_SIZE ? flush(), *_now++ = c : *_now++ = c)
#else
#if !defined(WIN32) && !defined(_WIN32)
#define putchar putchar_unlocked
#endif
#endif
        inline void write(char _x)
        {
            putchar(_x);
        }
        inline void write(char *const _x)
        {
            for (int i = 0; _x[i]; ++i)
                putchar(_x[i]);
        }
        inline void write(const char *__restrict _x)
        {
            for (int i = 0; _x[i]; ++i)
                putchar(_x[i]);
        }
        template <typename _T>
        inline void write(_T _x)
        {
            static char dight[39];
            int _len = 0;
            if (_x == 0)
            {
                putchar('0');
                return;
            }
            bool flag = false;
            if (_x < 0)
            {
                _x = -_x;
                flag = true;
            }
            while (_x)
            {
                dight[_len++] = (char)(_x % 10) + '0';
                _x /= 10;
            }
            if (flag)
                putchar('-');
            while (_len--)
                putchar(dight[_len]);
        }
        template <typename _T, typename... _G>
        inline void write(_T _x, _G... _y)
        {
            write(_x);
            write(_y...);
        }
#ifdef FAST_OUT
#undef putchar
#if !defined(WIN32) && !defined(_WIN32)
#define putchar putchar_unlocked
#endif
#endif
    }
}
template <typename T>
inline void ckmin(T &_x, T _y)
{
    if (_x > _y)
        _x = _y;
}
template <typename T>
inline void ckmax(T &_x, T _y)
{
    if (_x < _y)
        _x = _y;
}
using IO::INPUT::read;
using IO::OUTPUT::write;
using namespace std;
constexpr int N = 1e4 + 5;
constexpr int limit = 1e4;
int n, m, a[N];
struct Edge
{
    int next, to;
} edge[N * 2];
int head[N], num_edge;
inline void add_edge(int from, int to)
{
    edge[++num_edge].next = head[from];
    edge[num_edge].to = to;
    head[from] = num_edge;
}
int fa[N];
struct Tree
{
    int ch[2], fa;
    int fakesize, size;
    int fakesize2;
} tree[N];
#define lc(x) tree[x].ch[0]
#define rc(x) tree[x].ch[1]
#define fa(x) tree[x].fa
inline int calc(int x)
{
    return x * (x + 1) / 2;
}
inline bool check(int x)
{
    return rc(fa(x)) == x;
}
inline bool nroot(int x)
{
    return lc(fa(x)) == x || rc(fa(x)) == x;
}
inline void pushup(int x)
{
    tree[x].size = tree[lc(x)].size + tree[rc(x)].size + tree[x].fakesize + 1;
}
inline void rotate(int x)
{
    int y = fa(x), z = fa(y), k = check(x), w = tree[x].ch[k ^ 1];

    if (nroot(y))
        tree[z].ch[check(y)] = x;
    fa(x) = z;

    tree[x].ch[k ^ 1] = y;
    fa(y) = x;

    tree[y].ch[k] = w;
    if (w)
        fa(w) = y;

    pushup(y), pushup(x);
}
inline void splay(int x)
{
    while (nroot(x))
    {
        if (nroot(fa(x)))
            rotate(check(x) == check(fa(x)) ? fa(x) : x);
        rotate(x);
    }
}
inline void access(int x)
{
    for (int y = 0; x; x = fa(y = x))
    {
        splay(x);
        tree[x].fakesize += tree[rc(x)].size - tree[y].size;
        tree[x].fakesize2 += calc(tree[rc(x)].size) - calc(tree[y].size);
        rc(x) = y;
        pushup(x);
    }
}
inline int findroot(int x)
{
    access(x);
    splay(x);
    while (lc(x))
        x = lc(x);
    splay(x);
    return x;
}
int answer;
inline void link(int x)
{
    int y = fa[x];
    answer -= calc(tree[rc(findroot(y))].size);
    access(y);
    splay(y);
    splay(x);
    access(x);
    answer -= tree[x].fakesize2;
    fa(x) = y;
    tree[y].fakesize += tree[x].size;
    tree[y].fakesize2 += calc(tree[x].size);
    answer += calc(tree[rc(findroot(x))].size);
    pushup(y);
}
inline void cut(int x)
{
    int y = fa[x];
    answer -= calc(tree[rc(findroot(x))].size);
    access(x);
    splay(x);
    lc(x) = fa(lc(x)) = 0;
    answer += tree[x].fakesize2 + calc(tree[rc(findroot(y))].size);
    pushup(x);
}
vector<int> g[N];
vector<pair<int, int>> que[N];
int queryanswer[N];
int prime[N], tot, miu[N];
bool vis[N];
inline void init()
{
    for (int i = 1; i <= limit; ++i)
        for (int j = i; j <= limit; j += i)
            g[j].push_back(i);
    miu[1] = 1;
    for (int i = 2; i <= limit; ++i)
    {
        if (!vis[i])
        {
            prime[++tot] = i;
            miu[i] = -1;
        }
        for (int j = 1; j <= tot; ++j)
        {
            if (i * prime[j] > limit)
                break;
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0)
                break;
            miu[i * prime[j]] = -miu[i];
        }
    }
}
inline void work()
{
    read(n, m);
    for (int i = 1; i <= n; ++i)
        read(a[i]);
    fa[1] = n + 1;
    for (int i = 2; i <= n; ++i)
        read(fa[i]);
    for (int i = 1; i <= n; ++i)
        for (int j : g[a[i]])
            que[j].emplace_back(-1, i);
    int q = 0;
    for (int i = 1; i <= m; ++i)
    {
        int opt, u, c;
        read(opt, u);
        if (opt == 0)
        {
            read(c);
            for (int j : g[a[u]])
                que[j].emplace_back(0, u);
            a[u] = c;
            for (int j : g[a[u]])
                que[j].emplace_back(-1, u);
        }
        else
        {
            ++q;
            for (int j = u; j <= limit; j += u)
            {
                if (!miu[j / u])
                    continue;
                que[j].emplace_back(q, miu[j / u]);
            }
            queryanswer[q] = 0;
        }
    }
    for (int i = 1; i <= n; ++i)
        for (int j : g[a[i]])
            que[j].emplace_back(0, i);
    for (int kase = 1; kase <= limit; ++kase)
    {
        for (auto [x, y] : que[kase])
        {
            if (x == -1)
                link(y);
            else if (x == 0)
                cut(y);
            else
                queryanswer[x] += answer * y;
        }
        que[kase].clear();
    }
    for (int i = 1; i <= q; ++i)
        write(queryanswer[i], '\n');
}
signed main()
{
#ifdef PAPERDOG
    freopen("project.in", "r", stdin);
    freopen("project.out", "w", stdout);
#endif
    init();
    int T = 1;
    read(T);
    while (T--)
        work();
#ifdef FAST_OUT
    IO::OUTPUT::flush();
#endif
    return 0;
}