template <typename T>
struct Simpson
{
    using functype = function<T(T)>;
    functype f;
    Simpson(const functype &other) : f(other) {}
    auto simpson(T l, T r)
    {
        T mid = (l + r) / 2;
        return (r - l) * (f(l) + 4 * f(mid) + f(r)) / 6;
    }
    auto solve(T l, T r, T eps, T ans) -> T
    {
        T mid = (l + r) / 2;
        double fl = simpson(l, mid), fr = simpson(mid, r);
        if (abs(fl + fr - ans) <= 15 * eps)
            return fl + fr + (fl + fr - ans) / 15;
        return solve(l, mid, eps / 2, fl) + solve(mid, r, eps / 2, fr);
    }
    auto integral(T l, T r, T eps)
    {
        return solve(l, r, eps, simpson(l, r));
    }
};