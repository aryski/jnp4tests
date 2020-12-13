#include "computer.h"
#include <array>
#include <iostream>

// Operator == dla std::array jest constexpr dopiero od C++20.
template<class T, std::size_t N>
constexpr bool compare(std::array<T, N> const& arg1, std::array<T, N> const& arg2) {
    for (size_t i = 0; i < N; ++i)
        if (arg1[i] != arg2[i]) return false;
    return true;
}

using test_machine = Computer<4, bool>;
using mem_test2 = Program<D<Id("J"), Num<0>>, D<Id("P"), Num<0>>, D<Id("2"), Num<1>>, D<Id("GMD"), Num<0>>, Inc<Mem<Lea<Id("J")>>>, Dec<Mem<Lea<Id("2")>>>, Inc<Mem<Num<3>>>>;
    static_assert(compare(test_machine::boot<mem_test2>(), std::array<bool, 4>{1,0,0, 1}));

int main() {

}
