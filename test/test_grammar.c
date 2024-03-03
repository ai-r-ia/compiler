#include "test_grammar.h"
#include "../whole_include.h"

void test_grammar()
{
    Grammar grammar = init_grammar("grammar.txt");
    populateFirst(grammar);
    populateFollow(grammar);
    populateParseTable(grammar);

    // printf("FIRST and FOLLOW sets \n");
    // for (int i = 0; i < grammar->first->size; i++)
    // {
    //     printf("%s      First: ", grammarTokenKindString[i]);
    //     Vector rhs = (Vector)get(grammar->first, i);
    //     printVector(rhs);
    //     Vector rhs2 = (Vector)get(grammar->follow, i);
    //     printf("      Follow: ");
    //     printVector(rhs2);
    //     printf("\n");
    // }

    for (int r = 0; r < grammar->rules->size; r++)
    {
        Rule rule = (Rule)get(grammar->rules, r);
        Token null = init_token(TERMINAL, char_to_string("#"), NULL, 0, 0);
        Vector first = (Vector)get(grammar->first, (rule->NT)->type);
        if ((contains(first, null) && !grammar->nullable[rule->NT->type]))
        {
            error("nullable list incorrect");
        }
        if ((!contains(first, null) && grammar->nullable[rule->NT->type]))
        {
            error("nullable list incorrect");
        }
        // printf("%s      %d\n", rule->NT->lexeme_str->text, grammar->nullable[rule->NT->type]);
    }

    printParseTable(grammar);
}