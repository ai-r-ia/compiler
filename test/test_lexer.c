#include "test_lexer.h"

void test_lexer()
{
    info("testing LEXER");
    // Lexer lexer = init_lexer("test.txt");
    Lexer lexer = init_lexer("test/test_char.txt");
    // Lexer lexer = init_lexer("test_num.txt");

    Token tk = tokenize(lexer);
    // printf("fwd0 %d \n", lexer->fwd_ptr);

    Vector vec = init_vector(TOKEN);
    // push_back(vec, tk1);

    // Token tk = NULL;
    printf("%s \n", lexer->buff1);
    while ((lexer->fp))
    {
        // if(tk1_read)
        // printf("%s\n", token_type_list[tk->type]);
        push_back(vec, tk);
        tk = tokenize(lexer);
    }

    for (int i = 0; i < vec->size; i++)
    {
        printf("%s", token_type_list[((Token)get(vec, i))->type]);
        printf(" : %s", (char *)(((Token)get(vec, i))->lexeme_str)->text);

        printf("\n");
    }

    success("LEXER tested successfully.");
}