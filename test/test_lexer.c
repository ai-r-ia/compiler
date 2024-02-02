#include "test_lexer.h"

// Note: run this file from the test folder to avoid errors. Running from lexer.c or ../ directory will cause errors.
void test_lexer()
{
    info("testing LEXER");
    Lexer lexer = init_lexer("test.txt");

    Token tk = tokenize(lexer, true);
    Vector vec = init_vector(TOKEN);

    bool flag = false;

    while ((lexer->fp))
    {
        // printf("%s\n", token_type_list[tk->type]);
        push_back(vec, tk);

        if (tk->type == 57 && flag) // TK_ILLEGAL
        {
            tk = tokenize(lexer, false);
            flag = false;
        }
        if (!flag)
        {
            tk = tokenize(lexer, true);
            if (tk!= NULL && tk->type == 57)
                flag = true;
        }
    }

    for (int i = 0; i < vec->size; i++)
    {
        printf("%s\n", token_type_list[((Token)get(vec, i))->type]);
    }

    success("LEXER tested successfully.");
}