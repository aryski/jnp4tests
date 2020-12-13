#include "computer.h"
#include <array>
#include <iostream>

int main() {
    using test_machine = Computer<4, int>;

    using fail_undeclared_lea = Program<Mov<Lea<Id("a")>, Num<42>>>;
   constexpr auto x =  test_machine::boot<fail_undeclared_lea>();
}
