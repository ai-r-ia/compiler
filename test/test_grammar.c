#include "test_grammar.h"
#include "../whole_include.h"

void test_grammar()
{
    Grammar grammar = init_grammar("grammar.txt");
    populateFirst(grammar);
    populateFollow(grammar);
    // populateParseTable(grammar);

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

    // printf("PARSE TABLE");
    // for (int i = 0; i < grammar->parseTable->size; i++)
    // {
    //     Vector row = (Vector)get(grammar->parseTable, i);
    //     print("%s", grammarTokenKindString[i]);
    //     for (int j = 0; j < row->size; j++)
    //     {

    //         print("%s", token_type_list[i]);
    //         printRule((Rule)get(row, j));
    //     }
    // }
}