#include <iostream>
#include "vectors.h"

int main() {
    CVec3 u(1.f, 2.f, 3.f), v(2.f, 4.f, 6.f);

    u += v;

    std::cout << u;
}