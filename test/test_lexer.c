#include "test_lexer.h"

void test_lexer()
{
    info("testing LEXER");
    Lexer lexer = init_lexer("test/test.txt");

    Token tk = tokenize(lexer, true);
    Vector vec = init_vector(TOKEN);

    bool flag = false;

    printf("%s \n", lexer->buff1);
    while ((lexer->fp))
    {
        // printf("%s\n", token_type_list[tk->type]);
        push_back(vec, tk);

        if (tk->type == 57 && flag) // TK_ILLEGAL
        {
            tk = tokenize(lexer, false);
            flag = false;
        }
        else if (!flag)
        {
            tk = tokenize(lexer, true);
            if (tk != NULL && tk->type == 57)
                flag = true;
        }
    }

    for (int i = 0; i < vec->size; i++)
    {
        printf("%s", token_type_list[((Token)get(vec, i))->type]);
        if (((Token)get(vec, i))->type == 57)
            printf(" error: %s", (((Token)get(vec, i))->value)->text);
        printf("\n");
    }

    success("LEXER tested successfully.");
}