#include "computer.h"
#include <array>

// Operator == dla std::array jest constexpr dopiero od C++20.
template<class T, std::size_t N>
constexpr bool compare(std::array<T, N> const& arg1, std::array<T, N> const& arg2) {
    for (size_t i = 0; i < N; ++i)
        if (arg1[i] != arg2[i]) return false;
    return true;
}

using tmpasm_data = Program<
        Inc<Mem<Lea<Id("a")>>>,
        D<Id("a"), Num<0>>,
        D<Id("b"), Num<2>>,
        D<Id("c"), Num<3>>>;

int main() {
    static_assert(compare(
            Computer<4, uint32_t>::boot<tmpasm_data>(),
            std::array<uint32_t, 4>({1, 2, 3, 0})),
            "Failed [tmpasp_data].");
}
