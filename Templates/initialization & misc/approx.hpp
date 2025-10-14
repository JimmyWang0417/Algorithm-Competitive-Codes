auto approx(int p, int q, int A)
{
    int x = q, y = p, a = 1, b = 0;
    while (abs(a) > A)
    {
        swap(x, y), swap(a, b);
        a -= x / y * b;
        x %= y;
    }
    return make_pair(x, a);
}