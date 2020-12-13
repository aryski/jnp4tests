#include <array>
#include <iostream>
#include "computer.h"

using test_machine = Computer<4, int>;
// is syntax being verified even if the instruction is never executed?
using test_syntax_not_executed = Program<
    Jmp<Id("stop")>,
    Add<Num<0>, Num<0>>,
    Label<Id("stop")>
    >;
constexpr auto test_syntax_error_not_executed = test_machine::boot<test_syntax_not_executed>();

int main() {
    test_machine::boot<test_syntax_not_executed>();
}