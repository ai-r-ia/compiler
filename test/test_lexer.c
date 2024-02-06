#include "test_lexer.h"

void test_lexer()
{
    info("testing LEXER");
    Lexer lexer = init_lexer("test.txt");

    Token tk = tokenize(lexer);
    // printf("fwd0 %d \n", lexer->fwd_ptr);

    Vector vec = init_vector(TOKEN);
    // push_back(vec, tk1);

    bool flag = false;
    bool tk1_read = false;
    // Token tk = NULL;
    printf("%s \n", lexer->buff1);
    while ((lexer->fp))
    {
        // if(tk1_read)
        push_back(vec, tk);
        tk = tokenize(lexer);

        // if ((tk != NULL && tk->type == 57 && flag) || (tk1->type == 57 && !tk1_read)) // TK_ILLEGAL
        // {
        //     tk = tokenize(lexer, false);
        //     printf("fwd1 %d \n", lexer->fwd_ptr);
        //     flag = false;
        //     tk1_read = true;
        // }
        // else if (!flag)
        // {
        //     tk = tokenize(lexer, true);
        //     printf("fwd2 %d \n", lexer->fwd_ptr);
        //     if (tk != NULL && tk->type == 57)
        //         flag = true;
        // }

        // printf("%s\n", token_type_list[tk->type]);
        // printf("%s\n", (tk->value)->text);
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