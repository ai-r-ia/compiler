/* 
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/ 
#include "whole_include.h"

bool eof_retraction = false;
// Function to remove comments from a file
void remove_comments(const char *input_filename, const char *output_filename)
{
    FILE *input_file = fopen(input_filename, "r");
    if (input_file == NULL)
    {
        fprintf(stderr, "Error opening input file %s\n", input_filename);
        exit(1);
    }

    FILE *output_file = fopen(output_filename, "w");
    if (output_file == NULL)
    {
        fprintf(stderr, "Error opening output file %s\n", output_filename);
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), input_file))
    {
        char *comment_start = strchr(line, '%');
        if (comment_start != NULL)
        {
            *comment_start = '\0';
        }
        int i = strlen(line) - 1;
        while (i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' || line[i] == '\r'))
        {
            line[i] = '\0';
            i--;
        }
        printf("%s\n", line);
        fprintf(output_file, "%s\n", line);
    }

    fclose(input_file);
    fclose(output_file);
}
Lexer init_lexer(char *filename)
{
    Lexer lexer = (Lexer)malloc(sizeof(struct lexer));
    lexer->filename = filename;

    _openFile(lexer);

    lexer->buff1 = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    lexer->buff2 = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));

    lexer->BUFF_NUM = 1;
    _readFile(lexer);

    lexer->fwd_ptr = 0;
    lexer->lineNumber = 1;
    lexer->charNumber = 1;

    return lexer;
}

// delimiter or comment check
bool isDelimiter(char value)
{
    return (value == ' ') ||
           (value == '\t') ||
           (value == '\n') ||
           (value == '\0') ||
           (value == '%');
}

// Checks whether a character is [a-z] | [A-Z]
bool isLetter_a2z_A2Z(char value)
{
    return (value >= 'A' && value <= 'Z') || (value >= 'a' && value <= 'z');
}

//[a-z]
bool isLetter_a2z(char value)
{
    return (value >= 'a' && value <= 'z');
}

//[A-Z]
bool isLetter_A2Z(char value)
{
    return (value >= 'A' && value <= 'Z');
}

// [b-d]
bool isLetter_b2d(char value)
{
    return (value >= 'b' && value <= 'd');
}

// [e-z]
bool isLetter_e2z(char value)
{
    return (value >= 'e' && value <= 'z');
}

// Checks whether a character is [0-9]
bool isDigit_0_9(char value)
{
    return value >= '0' && value <= '9';
}

//[2-7]
bool isDigit_2_7(char value)
{
    return value >= '2' && value <= '7';
}

// for valid symbols (except [_],[#])
bool isSymbol(char value)
{
    return value == '<' || value == '>' || value == '%' || value == '[' ||
           value == ']' || value == ',' || value == ';' || value == ':' ||
           value == '.' || value == '(' || value == ')' || value == '+' ||
           value == '-' || value == '*' || value == '/' || value == '&' ||
           value == '@' || value == '~' || value == '=' || value == '!';
}

//checks for valid symbol table operator entries
bool isSymbolTableOperator(String str)
{
    return compare(str, char_to_string("+")) ||
        compare(str, char_to_string("-")) ||
        compare(str, char_to_string("*")) ||
        compare(str, char_to_string("/")) ||
        compare(str, char_to_string("&&&")) ||
        compare(str, char_to_string("@@@")) ||
        compare(str, char_to_string("~")) ||
        compare(str, char_to_string("<")) ||
        compare(str, char_to_string(">")) ||
        compare(str, char_to_string("<=")) ||
        compare(str, char_to_string(">=")) ||
        compare(str, char_to_string("==")) ||
        compare(str, char_to_string("!="));
}

int getKeyword(String word)
{
    for (int i = 0; i < 28; i++)
    {
        if (compare(char_to_string(keyword_type_list[i]), word))
            return i;
    }

    return -1;
}

Token tokenize_function(Lexer lexer, String lexeme, enum TOKEN_TYPE type, bool others)
{
    void *value;
    char *p;

    switch (type)
    {
    case TK_RNUM:
        value = (double *)malloc(sizeof(double));
        double d = strtod(lexeme->text, &p);
        value = &d;
        break;
    case TK_NUM:
        value = (int *)malloc(sizeof(int));
        int i = atoi(lexeme->text);
        value = &i;
        break;
    case TK_FIELDID:
    case TK_ID:
    case TK_FUNID:
    case TK_RUID:
    case TK_ILLEGAL:
    case TK_LT:
        value = (char *)malloc(sizeof(char));
        value = lexeme->text;
        break;
    default:

        printf("No coherent type provided to 'error_function'.");
        break;
    }

    if (isDelimiter(lexer->curr_char) || isSymbol(lexer->curr_char) || others)
    {
        return init_token(type, lexeme, value, lexer->lineNumber, lexer->charNumber);
    }

    while (((lexer->curr_char != ' ') && (lexer->curr_char != '\t') && (lexer->curr_char != '\n') && (lexer->curr_char != '\0') && (lexer->curr_char != '%') && (!isSymbol(lexer->curr_char))))
    {
        append(lexeme, lexer->curr_char);
        getNextCharacter(lexer);
    }

    retract(lexer, lexeme);
    Token ill_token = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
    sprintf(ill_token->error_msg, "Unknown pattern <%s>", lexeme->text);
    return ill_token;
}

char getNextCharacter(Lexer lexer)
{
    char res;
    if (lexer->BUFF_NUM == 1)
    {
        // lexer->buff_begin1;
        if (eof_retraction)
        {
            // printf("eof_retraction %d\n", eof_retraction);
            eof_retraction = false;
            return lexer->curr_char;
        }
        else
        {
            res = lexer->buff1[lexer->fwd_ptr];
            lexer->fwd_ptr++;
            if (lexer->fwd_ptr >= BUFFER_SIZE)
            {
                // printf("%s\n", lexer->buff1);
                lexer->fwd_ptr = 0;
                lexer->BUFF_NUM = 2;
                _readFile(lexer); // will load new data into buff2
            }
        }
    }
    else
    {
        if (eof_retraction)
        {
            // printf("eof_retraction %d\n", eof_retraction);
            eof_retraction = false;
            return lexer->curr_char;
        }
        else
        {
            res = lexer->buff2[lexer->fwd_ptr];
            lexer->fwd_ptr++;
            if (lexer->fwd_ptr >= BUFFER_SIZE)
            {
                // printf("%s\n", lexer->buff2);
                lexer->fwd_ptr = 0;
                lexer->BUFF_NUM = 1;
                _readFile(lexer); // will load new data into buff1
            }
        }
    }
    lexer->charNumber++;
    if (res == '\n')
    {
        lexer->lineNumber++;
        lexer->prevLineChar = lexer->curr_char;
        lexer->charNumber = 1;
    }

    return lexer->curr_char = res;
}

// retraction
void retract(Lexer lexer, String lexeme)
{
    pop_str(lexeme);
    char *buffer;
    if (lexer->BUFF_NUM == 1)
        buffer = lexer->buff1;
    else
        buffer = lexer->buff2;

    // eof
    // if (buffer[lexer->fwd_ptr] == '\0')
    //     eof_retraction = true;

    if ((lexer->fwd_ptr) != '\0')
        lexer->fwd_ptr--;
    else
        eof_retraction = true;

    lexer->charNumber--;
    if (buffer[lexer->fwd_ptr] == '\n')
    {
        lexer->lineNumber--;
        lexer->charNumber = lexer->prevLineChar;
    }
}

Token get_numeric_tk(Lexer lexer)
{
    String lexeme = init_str();

    while (lexer->fp && isDigit_0_9(lexer->curr_char))
    {
        append(lexeme, lexer->curr_char);
        getNextCharacter(lexer);
    }
    append(lexeme, lexer->curr_char);

    if (lexer->curr_char == '.')
    {
        return get_tk_rnum1(lexer, lexeme);
    }

    retract(lexer, lexeme);
    return tokenize_function(lexer, lexeme, TK_NUM, true);
}

Token get_tk_rnum1(Lexer lexer, String lexeme)
{

    getNextCharacter(lexer);
    append(lexeme, lexer->curr_char);
    if (isDigit_0_9(lexer->curr_char))
    {
        return get_tk_rnum2(lexer, lexeme);
    }
    // error
    retract(lexer, lexeme);
    retract(lexer, lexeme);
    return tokenize_function(lexer, lexeme, TK_NUM, true);
}

Token get_tk_rnum2(Lexer lexer, String lexeme)
{

    getNextCharacter(lexer);
    append(lexeme, lexer->curr_char);
    if (isDigit_0_9(lexer->curr_char))
    {
        return get_tk_rnum3(lexer, lexeme);
    }
    // error
    retract(lexer, lexeme);
    Token ill_token = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
    sprintf(ill_token->error_msg, "Unknown pattern <%s>", lexeme->text);
    return ill_token;
}

Token get_tk_rnum3(Lexer lexer, String lexeme)
{

    getNextCharacter(lexer);
    append(lexeme, lexer->curr_char);

    if (lexer->curr_char == 'E')
    {
        return get_tk_rnum4(lexer, lexeme);
    }
    // error
    retract(lexer, lexeme);
    return tokenize_function(lexer, lexeme, TK_RNUM, true);
}

Token get_tk_rnum4(Lexer lexer, String lexeme)
{

    getNextCharacter(lexer);
    append(lexeme, lexer->curr_char);
    if ((lexer->curr_char == '+') || (lexer->curr_char == '-'))
    {
        return get_tk_rnum5(lexer, lexeme);
    }
    else if (isDigit_0_9(lexer->curr_char))
    {
        return get_tk_rnum6(lexer, lexeme);
    }
    // error
    retract(lexer, lexeme);
    Token ill_token = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
    sprintf(ill_token->error_msg, "Unknown pattern <%s>", lexeme->text);
    return ill_token;
}

Token get_tk_rnum5(Lexer lexer, String lexeme)
{

    getNextCharacter(lexer);
    append(lexeme, lexer->curr_char);
    if (isDigit_0_9(lexer->curr_char))
    {
        return get_tk_rnum6(lexer, lexeme);
    }

    // error
    retract(lexer, lexeme);
    Token ill_token = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
    sprintf(ill_token->error_msg, "Unknown pattern <%s>", lexeme->text);
    return ill_token;
}

Token get_tk_rnum6(Lexer lexer, String lexeme)
{

    // getNextCharacter(lexer);
    getNextCharacter(lexer);
    append(lexeme, lexer->curr_char);
    if (isDigit_0_9(lexer->curr_char))
    {
        return tokenize_function(lexer, lexeme, TK_RNUM, true);
    }
    // error
    retract(lexer, lexeme);
    Token ill_token = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
    sprintf(ill_token->error_msg, "Unknown pattern <%s>", lexeme->text);
    return ill_token;
}

Token get_char_tk(Lexer lexer)
{
    String lexeme = init_str();
    append(lexeme, lexer->curr_char);

    if (isLetter_b2d(lexer->curr_char))
    {
        return after_b2d(lexer, lexeme);
    }
    if (lexer->curr_char == 'a' || isLetter_e2z(lexer->curr_char))
    {
        return get_tk_fieldid(lexer, lexeme);
    }
    if (lexer->curr_char == '_')
    {
        return get_tk_funid0(lexer, lexeme);
    }
    if (lexer->curr_char == '#')
    {
        return get_tk_ruid0(lexer, lexeme);
    }

    // error --> should never occur here
    // retract(lexer, lexeme);
    Token ill_token = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
    sprintf(ill_token->error_msg, "Unknown Symbol <%s>", lexeme->text);
    return ill_token;
}

Token after_b2d(Lexer lexer, String lexeme)
{

    getNextCharacter(lexer);
    append(lexeme, lexer->curr_char);

    if (isDigit_2_7(lexer->curr_char))
        return get_tk_id2(lexer, lexeme);
    if (isLetter_a2z(lexer->curr_char))
        return get_tk_fieldid(lexer, lexeme);

    // error
    retract(lexer, lexeme);
    Token ill_token = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
    sprintf(ill_token->error_msg, "Unknown pattern <%s>", lexeme->text);
    return ill_token;
}

Token get_tk_fieldid(Lexer lexer, String lexeme)
{
    bool flag = false;
    while (lexer->fp && isLetter_a2z(lexer->curr_char))
    {
        if (flag)
        {
            append(lexeme, lexer->curr_char);
        }

        getNextCharacter(lexer);
        flag = true;
    }
    append(lexeme, lexer->curr_char);
    retract(lexer, lexeme);

    int keyword = getKeyword(lexeme);
    if (keyword != -1)
    {
        return init_token(keyword_token_value[keyword], lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
    }

    return tokenize_function(lexer, lexeme, TK_FIELDID, true);
}

Token get_tk_id2(Lexer lexer, String lexeme)
{
    getNextCharacter(lexer);
    while (lexer->fp && isLetter_b2d(lexer->curr_char))
    {

        append(lexeme, lexer->curr_char);
        getNextCharacter(lexer);

        if (isDigit_2_7(lexer->curr_char))
        {
            append(lexeme, lexer->curr_char);
            return get_tk_id3(lexer, lexeme);
        }
    }

    append(lexeme, lexer->curr_char);
    retract(lexer, lexeme);
    return tokenize_function(lexer, lexeme, TK_ID, true);
}

Token get_tk_id3(Lexer lexer, String lexeme)
{

    bool flag = false;
    while (lexer->fp && isDigit_2_7(lexer->curr_char))
    {
        if (flag)
        {
            append(lexeme, lexer->curr_char);
        }
        getNextCharacter(lexer);
        flag = true;
    }

    append(lexeme, lexer->curr_char);
    retract(lexer, lexeme);

    if (lexeme->size > 20)
    {
        Token ret = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        ret->error_msg = "Variable Identifier is longer than the prescribed length of 20 characters.";
        return ret;
    }
    return tokenize_function(lexer, lexeme, TK_ID, true);
}

Token get_tk_funid0(Lexer lexer, String lexeme)
{

    getNextCharacter(lexer);
    append(lexeme, lexer->curr_char);
    if (isLetter_a2z_A2Z(lexer->curr_char))
    {
        return get_tk_funid1(lexer, lexeme); // ret fn 11
    }
    // error
    retract(lexer, lexeme);
    Token ill_token = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
    sprintf(ill_token->error_msg, "Unknown pattern <%s>", lexeme->text);
    return ill_token;
}

Token get_tk_funid1(Lexer lexer, String lexeme)
{

    bool flag = false;
    while (lexer->fp && isLetter_a2z_A2Z(lexer->curr_char))
    {
        if (flag)
        {
            append(lexeme, lexer->curr_char);
        }
        getNextCharacter(lexer);

        flag = true;
    }

    append(lexeme, lexer->curr_char);

    if (isDigit_0_9(lexer->curr_char))
    {
        return get_tk_funid3(lexer, lexeme);
    }

    retract(lexer, lexeme);

    if (!isDigit_0_9(lexer->curr_char))
    {
        int keyword = getKeyword(lexeme);
        if (keyword_token_value[keyword] == 17)
        {
            return init_token(TK_MAIN, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        }
    }

    if (lexeme->size > 30)
    {
        Token ret = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        ret->error_msg = "Function Identifier is longer than the prescribed length of 30 characters.";
        return ret;
    }
    return tokenize_function(lexer, lexeme, TK_FUNID, true);
}

Token get_tk_funid3(Lexer lexer, String lexeme)
{

    bool flag = false;
    while (lexer->fp && isDigit_0_9(lexer->curr_char))
    {
        if (flag)
        {
            append(lexeme, lexer->curr_char);
        }
        getNextCharacter(lexer);
        flag = true;
    }

    append(lexeme, lexer->curr_char);
    retract(lexer, lexeme);
    return tokenize_function(lexer, lexeme, TK_FUNID, true);
}

Token get_tk_ruid0(Lexer lexer, String lexeme)
{

    getNextCharacter(lexer);
    append(lexeme, lexer->curr_char);
    if (isLetter_a2z(lexer->curr_char))
    {
        return get_tk_ruid1(lexer, lexeme); // ret fn 15
    }
    // error
    retract(lexer, lexeme);
    Token ill_token = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
    sprintf(ill_token->error_msg, "Unknown pattern <%s>", lexeme->text);
    return ill_token;
}

Token get_tk_ruid1(Lexer lexer, String lexeme)
{

    bool flag = false;
    while (lexer->fp && isLetter_a2z(lexer->curr_char))
    {
        if (flag)
        {
            append(lexeme, lexer->curr_char);
        }
        getNextCharacter(lexer);
        flag = true;
    }
    append(lexeme, lexer->curr_char);
    retract(lexer, lexeme);
    return tokenize_function(lexer, lexeme, TK_RUID, true);
}

Token get_symbol_tk(Lexer lexer)
{
    String lexeme = init_str();
    append(lexeme, lexer->curr_char);

    if (lexer->curr_char == '<')
    {
        getNextCharacter(lexer);

        if (lexer->curr_char == '-')
        {
            append(lexeme, lexer->curr_char);
            getNextCharacter(lexer);

            if (lexer->curr_char == '-')
            {
                append(lexeme, lexer->curr_char);
                getNextCharacter(lexer);

                if (lexer->curr_char == '-')
                {
                    append(lexeme, lexer->curr_char);
                    return init_token(TK_ASSIGNOP, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
                }

                // error
                append(lexeme, lexer->curr_char);
                retract(lexer, lexeme);
                Token ill_token = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
                sprintf(ill_token->error_msg, "Unknown pattern <%s>", lexeme->text);
                return ill_token;
            }

            // error
            append(lexeme, lexer->curr_char);
            retract(lexer, lexeme);
            retract(lexer, lexeme);

            return tokenize_function(lexer, lexeme, TK_LT, true);
        }
        if (lexer->curr_char == '=')
        {
            append(lexeme, lexer->curr_char);
            return init_token(TK_LE, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        }

        append(lexeme, lexer->curr_char);
        retract(lexer, lexeme);

        return init_token(TK_LT, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
    }
    if (lexer->curr_char == '>')
    {
        getNextCharacter(lexer);

        if (lexer->curr_char == '=')
        {
            append(lexeme, lexer->curr_char);
            return init_token(TK_GE, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        }

        append(lexeme, lexer->curr_char);
        retract(lexer, lexeme);

        return init_token(TK_GT, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
    }

    if (lexer->curr_char == '&')
    {
        getNextCharacter(lexer);

        if (lexer->curr_char == '&')
        {
            append(lexeme, lexer->curr_char);
            getNextCharacter(lexer);

            if (lexer->curr_char == '&')
            {
                append(lexeme, lexer->curr_char);
                return init_token(TK_AND, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
            }

            // error
            append(lexeme, lexer->curr_char);
            retract(lexer, lexeme);
            Token ill_token = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
            sprintf(ill_token->error_msg, "Unknown pattern <%s>", lexeme->text);
            return ill_token;
        }

        // error
        append(lexeme, lexer->curr_char);
        retract(lexer, lexeme);
        Token ill_token = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        sprintf(ill_token->error_msg, "Unknown Symbol <%s>", lexeme->text);
        return ill_token;
    }

    if (lexer->curr_char == '@')
    {
        getNextCharacter(lexer);

        if (lexer->curr_char == '@')
        {
            append(lexeme, lexer->curr_char);
            getNextCharacter(lexer);

            if (lexer->curr_char == '@')
            {
                append(lexeme, lexer->curr_char);
                return init_token(TK_OR, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
            }

            // error
            append(lexeme, lexer->curr_char);
            retract(lexer, lexeme);

            Token ill_token = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
            sprintf(ill_token->error_msg, "Unknown pattern <%s>", lexeme->text);
            return ill_token;
        }

        // error
        append(lexeme, lexer->curr_char);
        retract(lexer, lexeme);

        Token ill_token = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        sprintf(ill_token->error_msg, "Unknown Symbol <%s>", lexeme->text);
        return ill_token;
    }

    if (lexer->curr_char == '=')
    {
        getNextCharacter(lexer);

        if (lexer->curr_char == '=')
        {
            append(lexeme, lexer->curr_char);
            return init_token(TK_EQ, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        }

        // error
        append(lexeme, lexer->curr_char);
        retract(lexer, lexeme);

        Token ill_token = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        sprintf(ill_token->error_msg, "Unknown Symbol <%s>", lexeme->text);
        return ill_token;
    }

    if (lexer->curr_char == '!')
    {
        getNextCharacter(lexer);

        if (lexer->curr_char == '=')
        {
            append(lexeme, lexer->curr_char);
            return init_token(TK_NE, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        }

        // error
        append(lexeme, lexer->curr_char);
        retract(lexer, lexeme);

        Token ill_token = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        sprintf(ill_token->error_msg, "Unknown Symbol <%s>", lexeme->text);
        return ill_token;
    }

    if (lexer->curr_char == '[')
        return init_token(TK_SQL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == ']')
        return init_token(TK_SQR, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == ',')
        return init_token(TK_COMMA, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == ';')
        return init_token(TK_SEM, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == ':')
        return init_token(TK_COLON, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '.')
        return init_token(TK_DOT, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '(')
        return init_token(TK_OP, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == ')')
        return init_token(TK_CL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '+')
        return init_token(TK_PLUS, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '-')
        return init_token(TK_MINUS, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '*')
        return init_token(TK_MUL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '/')
        return init_token(TK_DIV, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '~')
        return init_token(TK_NOT, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    // error --> should never occur here
    append(lexeme, lexer->curr_char);
    retract(lexer, lexeme);

    Token ill_token = init_token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
    sprintf(ill_token->error_msg, "Unknown Symbol <%s>", lexeme->text);
    return ill_token;
}

Token getNextToken(Lexer lexer)
{
    getNextCharacter(lexer);

    // whitespaces
    if (lexer->curr_char == ' ' || lexer->curr_char == '\t' || lexer->curr_char == '\n')
        return getNextToken(lexer);

    // eof
    if (lexer->curr_char == '\0')
    {
        _closeFile(lexer);
        return NULL;
    }

    if (lexer->curr_char == '%')
    {
        while (lexer->curr_char != '\n' && lexer->curr_char != '\0')
        {
            getNextCharacter(lexer);
            // append(lexeme, lexer->curr_char);
        }

        return getNextToken(lexer);
    }

    // initial state for letter based tokens
    if (isLetter_a2z(lexer->curr_char) || lexer->curr_char == '_' || lexer->curr_char == '#')
        return get_char_tk(lexer);

    // initial state for digit based tokens
    if (isDigit_0_9(lexer->curr_char))
        return get_numeric_tk(lexer);

    // initial state for symbolic tokens
    if (isSymbol(lexer->curr_char))
        return get_symbol_tk(lexer);

    String illegal = init_str();
    append(illegal, lexer->curr_char);
    Token ill_token = init_token(TK_ILLEGAL, illegal, illegal->text, lexer->lineNumber, lexer->charNumber);
    sprintf(ill_token->error_msg, "Unknown Symbol <%s>", illegal->text);
    return ill_token;
}

// private functions (internal)

void _openFile(Lexer lexer)
{
    lexer->fp = fopen(lexer->filename, "r");
    if (lexer->fp == NULL)
    {
        char err_text[300];
        sprintf(err_text, "Error in opening file: %s", lexer->filename);
        error(err_text);
        exit(1);
    }
}

// reads file into one of the buffers buff1 or buff2 depending on BUFF_NUM
void _readFile(Lexer lexer)
{

    char err_text[300];

    // eof reached
    if (!lexer->fp)
    {
        sprintf(err_text, "File: %s is closed", lexer->filename);
        error(err_text);
        return;
        // exit(1);
    }

    size_t fr;
    char *buff;
    if (lexer->BUFF_NUM == 1)
        buff = lexer->buff1;
    else
        buff = lexer->buff2;

    memset(buff, '\0', BUFFER_SIZE + 1);
    fr = fread(buff, 1, BUFFER_SIZE, lexer->fp);

    if (fr != BUFFER_SIZE)
    {
        // file reading error
        if (ferror(lexer->fp))
        {
            sprintf(err_text, "Error while reading file: %s", lexer->filename);
            error(err_text);
            exit(1);
        }
        clearerr(lexer->fp);
    }
}

void _closeFile(Lexer lexer)
{
    if (fclose(lexer->fp) != 0)
    {
        char err_text[300];
        sprintf(err_text, "Error in closing file: %s", lexer->filename);
        error(err_text);
        exit(1);
    }

    lexer->fp = NULL;
}
