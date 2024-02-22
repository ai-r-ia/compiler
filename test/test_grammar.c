#include "test_grammar.h"
#include "../whole_include.h"

void test_grammar()
{
    Grammar grammar = init_grammar("real_grammar.txt");
    populateFirst(grammar);
    populateFollow(grammar);

    printf("FIRST and FOLLOW sets \n");
    for (int i = 0; i < grammar->first->size; i++)
    {
        printf("%s      First: ", grammarTokenKindString[i]);
        Vector rhs = (Vector)get(grammar->first, i);
        printVector(rhs);
        Vector rhs2 = (Vector)get(grammar->follow, i);
        printf("      Follow: ");
        printVector(rhs2);
        printf("\n");
    }
}