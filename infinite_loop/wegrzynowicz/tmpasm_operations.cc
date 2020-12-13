#include "computer.h"
#include <array>

// Operator == dla std::array jest constexpr dopiero od C++20.
template<class T, std::size_t N>
constexpr bool compare(std::array<T, N> const& arg1, std::array<T, N> const& arg2) {
    for (size_t i = 0; i < N; ++i)
        if (arg1[i] != arg2[i]) return false;
    return true;
}

using tmpasm_operations = Program<
        D<Id("a"), Num<4>>,
        D<Id("b"), Num<3>>,
        D<Id("c"), Num<2>>,
        D<Id("d"), Num<1>>,
        Add<Mem<Lea<Id("a")>>, Mem<Lea<Id("c")>>>,
        Sub<Mem<Lea<Id("b")>>, Mem<Lea<Id("d")>>>,
        Mov<Mem<Lea<Id("c")>>, Num<0>>,
        Mov<Mem<Lea<Id("d")>>, Num<0>>>;


int main() {
    static_assert(compare(
            Computer<5, int64_t>::boot<tmpasm_operations>(),
            std::array<int64_t, 5>({6, 2, 0, 0, 0})),
            "Failed [tmpasp_operations].");
}
