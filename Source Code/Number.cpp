#include"Number.h"

int gcd(int a, int b) {
    return b > 0 ? gcd(b, a % b) : a;
}

int lcm(int a, int b)
{
    return a*b/gcd(a,b);
}
