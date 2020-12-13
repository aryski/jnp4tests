//
// Tests by Kamil Ciebiera on WTFPL
//

#include "computer.h"
#include <array>
#include <iostream>
#include <assert.h>
using namespace std;

#define Var(id) Mem<Lea<Id(id)>>
#define Decl(id, b) D<Id(id), Num<b>>
#define CmpVV(id1, id2) Cmp<Var(id1), Var(id2)>
#define CmpVN(id, N) Cmp<Var(id), Num<N>>
#define CmpNV(N, id) Cmp<Num<N>, Var(id)>
#define Jump(id) Jmp<Id(id)>
#define Jp0(id) Jz<Id(id)>
#define Jpneg(id) Js<Id(id)>
#define Ad(id, V) Add<Var(id), V>
#define Sb(id, V) Sub<Var(id), V>
#define Incc(id) Inc<Var(id)>
#define Decc(id) Dec<Var(id)>
#define Movv(V1, V2) Mov<V1, V2>
#define MemA(addr) Mem<Num<addr>>
#define Lb(id) Label<Id(id)>
#define Numm(n) Num<n>

constexpr int pot2(int n) {
    int pot = 1;
    while (pot < n){
        pot*=2;
    }
    return pot;
}

constexpr bool is_prime(int p){
    if (p < 2)
        return false;
    int check = 2;
    while (check*check <= p){
        if(p % check == 0)
            return false;
        check++;
    }
    return true;
}

using myComputer = Computer<1000, int>;

template<int N>
using pot2tmpasm = Program<
        Decl("n", N),
        Decl("pot2", 1),

        Lb("Check"),
        CmpVV("n", "pot2"),
        Jpneg("end"),
        Jp0("End"),
        Ad("pot2", Var("pot2")),
        Jump("check"),

        Lb("END"),
        Movv(MemA(0), Var("pot2"))>;

template<int N>
struct pot2_test {
    static_assert(myComputer::boot<pot2tmpasm<N>>()[0] == pot2(N), "TEST fail");
};

pot2_test<1> a;
pot2_test<100> b;
pot2_test<2130> c;

template<int p>
using primeTmpasm = Program<
        Decl("p", p),
        Decl("check", 2),

        CmpVN("p", 2),
        Jpneg("no"),

        Lb("again"),
        CmpVV("p", "check"),
        Jp0("yes"),
        Jump("mod"),
        Lb("not0"),
        Incc("check"),
        Jump("again"),

        Lb("mod"),
        Decl("pom", 0),
        Movv(Var("pom"), Var("check")),
        Lb("add"),
        Ad("pom", Var("check")),
        CmpVV("p", "pom"),
        Jpneg("not0"),
        Jp0("no"),
        Jump("add"),

        Lb("no"),
        Movv(MemA(0), Numm(0)),
        Jump("end"),

        Lb("yes"),
        Movv(MemA(0), Numm(1)),
        Jump("end"),

        Lb("END")>;

template<int N>
struct prime_test {
    static_assert(myComputer::boot<primeTmpasm<N>>()[0] == is_prime(N), "TEST fail");
};

prime_test<0> p0;
prime_test<1> p1;
prime_test<2> p2;
prime_test<4> p4;
prime_test<5> p5;
prime_test<19> p19;
prime_test<21> p21;
prime_test<22> p22;
prime_test<166> p166;
prime_test<23> p23;
prime_test<168> p168;


constexpr int sMAX = 31; // 132 max without segm error

template<int N>
using sito = Program<
        Decl("pom", 0),
        Decl("it", 1),

        Lb("next"),
        Incc("it"),
        CmpNV(N, "it"),
        Jpneg("end"),
        Cmp<Mem<Var("it")>, Numm(0)>,
        Jp0("Pier"),
        Jump("next"),

        Lb("pier"),
        Movv(Var("pom"), Var("it")),
        Lb("again"),
        Ad("pom", Var("it")),
        CmpNV(N, "pom"),
        Jpneg("next"),
        Movv(Mem<Var("pom")>, Numm(1)),
        Jump("again"),


        Lb("end"),
        Movv(MemA(0), Numm(1)),
        Movv(MemA(1), Numm(1))>;

constexpr auto sito_test = myComputer::boot<sito<sMAX>>();
int main(){
    for(int i = 0; i <= sMAX; i++)
        assert(sito_test[i] == !is_prime(i));
}
