#pragma once
#include "lagrange.hpp"
namespace polynomial
{
    auto linearRecurrence(int n, poly a, poly f)
    {
        int m = (int)a.size();
        f = poly{1} - f;
        a = a * f;
        a.resize(m);
        return poly::bostanMori(n, a, f);
    }
    auto linearRecurrence(int n, poly a, poly f, poly p)
    {
        int k = (int)a.size(), m = (int)p.size() - 1;
        auto C = poly{1} - f;
        auto B = a * C;
        B.resize(k);
        vector<int> X(m + 1);
        iota(X.begin(), X.end(), k);
        auto Y = lagrange().eval(p, X);
        B.insert(B.end(), Y.begin(), Y.end());

        auto A = B * C.fit(m + k + 1).inv();
        A.resize(m + k + 1);

        auto Q = C * poly{1, -1}.fit(m + 2).pow(m + 1);
        auto P = A * Q;
        P.resize(k + m + 1);
        return poly::bostanMori(n, P, Q);
    }
}
