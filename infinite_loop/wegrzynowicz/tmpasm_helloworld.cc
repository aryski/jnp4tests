#include "computer.h"
#include <array>

// Operator == dla std::array jest constexpr dopiero od C++20.
template<class T, std::size_t N>
constexpr bool compare(std::array<T, N> const& arg1, std::array<T, N> const& arg2) {
    for (size_t i = 0; i < N; ++i)
        if (arg1[i] != arg2[i]) return false;
    return true;
}

using tmpasm_helloworld = Program<
        Mov<Mem<Mem<Num<10>>>, Num<'h'>>,
        Inc<Mem<Num<10>>>,
        Mov<Mem<Mem<Num<10>>>, Num<'e'>>,
        Inc<Mem<Num<10>>>,
        Mov<Mem<Mem<Num<10>>>, Num<'l'>>,
        Inc<Mem<Num<10>>>,
        Mov<Mem<Mem<Num<10>>>, Num<'l'>>,
        Inc<Mem<Num<10>>>,
        Mov<Mem<Mem<Num<10>>>, Num<'o'>>,
        Inc<Mem<Num<10>>>,
        Mov<Mem<Mem<Num<10>>>, Num<' '>>,
        Inc<Mem<Num<10>>>,
        Mov<Mem<Mem<Num<10>>>, Num<'w'>>,
        Inc<Mem<Num<10>>>,
        Mov<Mem<Mem<Num<10>>>, Num<'o'>>,
        Inc<Mem<Num<10>>>,
        Mov<Mem<Mem<Num<10>>>, Num<'r'>>,
        Inc<Mem<Num<10>>>,
        Mov<Mem<Mem<Num<10>>>, Num<'l'>>,
        Inc<Mem<Num<10>>>,
        Mov<Mem<Mem<Num<10>>>, Num<'d'>>>;

int main() {
    static_assert(compare(
            Computer<11, char>::boot<tmpasm_helloworld>(),
            std::array<char, 11>({'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'})),
            "Failed [tmpasm_helloworld].");
}
