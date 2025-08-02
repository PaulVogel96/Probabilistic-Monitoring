#include <List.hpp>
#include "State.hpp"
#include "ProbTransition.hpp"
#include "ProbStatemachine.hpp"

int main()
{
    State<ProbTransition> A("A");
    State<ProbTransition> B("B");
    State<ProbTransition> E("E");

    ProbTransition s1(&A, &B, 1.0, 'a');
    ProbTransition s2(&B, &B, 1.0, 'a');
    ProbTransition h1(&B, &A, 1.0, 'b');
    ProbTransition h2(&A, &E, 1.0, 'b');

    ProbStatemachine Automat(&A);
    return 0;
}