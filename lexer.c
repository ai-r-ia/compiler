#include "whole_include.h"

Lexer init_lexer(char *filename)
{
    Lexer lexer = (Lexer)malloc(sizeof(struct lexer));
    lexer->filename = filename;

    _openFile(lexer);

    lexer->BUFF_SIZE1 = BUFFER_SIZE;
    lexer->BUFF_SIZE2 = BUFFER_SIZE;
    lexer->buff1 = (char *)malloc(sizeof(char) * (lexer->BUFF_SIZE1 + 1));
    lexer->buff2 = (char *)malloc(sizeof(char) * (lexer->BUFF_SIZE2 + 1));

    lexer->BUFF_NUM = 1;
    _readFile(lexer);

    // lexer->buff_begin1 = 0;
    // lexer->buff_begin2 = 0;
    lexer->buffp1 = 0;
    lexer->buffp2 = 0;
    lexer->fwd_ptr = 0;
    lexer->lineNumber = 1;
    lexer->charNumber = 1;
    // _closeFile(lexer);
    return lexer;
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

char getNextCharacter(Lexer lexer) // TODO: test this and work out doublebuffering mechanism
{
    char res;
    if (lexer->BUFF_NUM == 1)
    {
        // lexer->buff_begin1;
        res = lexer->buff1[lexer->fwd_ptr];
        lexer->fwd_ptr++;
        if (lexer->fwd_ptr >= lexer->BUFF_SIZE1)
        {
            lexer->BUFF_NUM = 2;
            _readFile(lexer); // will load new data into buff2
        }
    }
    else
    {
        res = lexer->buff2[lexer->fwd_ptr];
        lexer->fwd_ptr++;
        if (lexer->fwd_ptr >= lexer->BUFF_SIZE2)
        {
            lexer->BUFF_NUM = 1;
            _readFile(lexer); // will load new data into buff1
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

/* check at the bottom of lexer.c for all TD states

In digit based tokens: 10 states
17: if [.]
18: ret tk_num        NOTE: removed
19: if [0-9] after 17
20: if [0-9] after 19
21: if [E]
22: if [+|-]
23: if [0-9] after 22
24: if [0-9] after 23 NOTE: removed
25: ret tk_rnum       NOTE: removed
*/
Token get_numeric_tk(Lexer lexer)
{
    String lexeme = init_str();
    int state = 2;

    while (lexer->fp && isDigit_0_9(lexer->curr_char))
    {
        append(lexeme, lexer->curr_char);
        getNextCharacter(lexer);
    }

    if (lexer->curr_char == '.')
    {
        append(lexeme, lexer->curr_char);
        state = 17; // ret fn 17
    }

    return init_Token(TK_NUM, lexeme, lexer->lineNumber, lexer->charNumber);

    switch (state)
    {
    case 17:
        getNextCharacter(lexer);
        if (isDigit_0_9(lexer->curr_char))
        {
            append(lexeme, lexer->curr_char);
            state = 19; // ret fn 19
        }
        // error
        return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);

    case 19:
        getNextCharacter(lexer);
        if (isDigit_0_9(lexer->curr_char))
        {
            append(lexeme, lexer->curr_char);
            state = 20; // ret fn 20
        }
        // error
        return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);

    case 20:
        getNextCharacter(lexer);
        if (lexer->curr_char == 'E')
        {
            append(lexeme, lexer->curr_char);
            state = 21; // ret fn 21
        }
        return init_Token(TK_RNUM, lexeme, lexer->lineNumber, lexer->charNumber);

    case 21:
        getNextCharacter(lexer);
        if ((lexer->curr_char == '+') || (lexer->curr_char == '-'))
        {
            append(lexeme, lexer->curr_char);
            state = 22; // ret fn 22
        }
        else if (isDigit_0_9(lexer->curr_char))
        {
            append(lexeme, lexer->curr_char);
            state = 23; // ret fn 23
        }
        // error
        return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);

    case 22:
        getNextCharacter(lexer);
        if (isDigit_0_9(lexer->curr_char))
        {
            append(lexeme, lexer->curr_char);
            state = 23; // ret fn 23
        }
        // error
        return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);

    case 23:
        getNextCharacter(lexer);
        if (isDigit_0_9(lexer->curr_char))
        {
            append(lexeme, lexer->curr_char);
            return init_Token(TK_RNUM, lexeme, lexer->lineNumber, lexer->charNumber);
        }
        // error
        return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);
    }
}

/*In character based tokens : 13 states
4 : if[b - d]
5 : if[a | e - z] | [a - z] and check Keyword
6 : ret tk_fieldid
7 : from 4 accepts[2 - 7] to transition, loops on[b - d]
8 : loops on[2 - 7]
9 : ret tk_id NOTE: __REMOVED__
10 : if[_]
11 : loops on[a - z | A - Z], check keyword
12 : loops on[0 - 9]
13 : ret tk_funid  NOTE: __REMOVED__
14 : if[#]
15 : loops on[a - z]
16 : ret tk_ruid      NOTE: __REMOVED__
*/
Token get_char_tk(Lexer lexer)
{
    String lexeme = init_str();
    append(lexeme, lexer->curr_char);
    int keyword;
    bool flag;
    int state = 1;

    if (isLetter_b2d(lexer->curr_char))
        state = 4; // ret fn 4
    if (lexer->curr_char == 'a' || isLetter_e2z(lexer->curr_char))
        state = 5; // ret fn 5
    if (lexer->curr_char == '_')
        state = 10; // ret fn 10
    if (lexer->curr_char == '#')
        state = 14; // ret fn 14

    // error --> should never occur here
    return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);

    switch (state)
    {
    case 4:
        getNextCharacter(lexer);
        if (isDigit_2_7(lexer->curr_char))
        {
            append(lexeme, lexer->curr_char);
            state = 7; // ret fn 7
        }
        if (isLetter_a2z(lexer->curr_char))
        {
            append(lexeme, lexer->curr_char);
            state = 5; // ret fn 5
        }
        // error
        return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);

    case 5:
        flag = false;
        while (lexer->fp && isLetter_a2z(lexer->curr_char))
        {
            if (flag)
                append(lexeme, lexer->curr_char);

            keyword = getKeyword(lexeme);
            if (keyword != -1)
                // TODO: check init_token type
                return init_Token(keyword_token_value[keyword], lexeme, lexer->lineNumber, lexer->charNumber);

            getNextCharacter(lexer);
            flag = true;
        }

        return init_Token(TK_FIELDID, lexeme, lexer->lineNumber, lexer->charNumber);

    case 7:
        flag = false;
        while (lexer->fp && isLetter_b2d(lexer->curr_char))
        {
            if (flag)
                append(lexeme, lexer->curr_char);

            getNextCharacter(lexer);

            if (isDigit_2_7(lexer->curr_char))
            {
                append(lexeme, lexer->curr_char);
                state = 8; // ret fn 8
            }

            flag = true;
        }

        return init_Token(TK_ID, lexeme, lexer->lineNumber, lexer->charNumber);

    case 8:
        flag = false;
        while (lexer->fp && isLetter_b2d(lexer->curr_char))
        {
            if (flag)
                append(lexeme, lexer->curr_char);
            getNextCharacter(lexer);
            flag = true;
        }

        return init_Token(TK_ID, lexeme, lexer->lineNumber, lexer->charNumber);

    case 10:
        getNextCharacter(lexer);
        if (isLetter_a2z_A2Z(lexer->curr_char))
        {
            append(lexeme, lexer->curr_char);
            state = 11; // ret fn 11
        }
        // error
        return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);

    case 11:
        flag = false;
        while (lexer->fp && isLetter_a2z_A2Z(lexer->curr_char))
        {
            if (flag)
                append(lexeme, lexer->curr_char);

            keyword = getKeyword(lexeme);
            if (keyword == 17)
                return init_Token(TK_MAIN, lexeme, lexer->lineNumber, lexer->charNumber);

            getNextCharacter(lexer);

            if (isDigit_0_9(lexer->curr_char))
            {
                append(lexeme, lexer->curr_char);
                state = 12; // ret fn 12
            }

            flag = true;
        }

        return init_Token(TK_FUNID, lexeme, lexer->lineNumber, lexer->charNumber);

    case 12:
        flag = false;
        while (lexer->fp && isDigit_0_9(lexer->curr_char))
        {
            if (flag)
                append(lexeme, lexer->curr_char);
            getNextCharacter(lexer);
            flag = true;
        }

        return init_Token(TK_FUNID, lexeme, lexer->lineNumber, lexer->charNumber);

    case 14:
        getNextCharacter(lexer);
        if (isLetter_a2z(lexer->curr_char))
        {
            append(lexeme, lexer->curr_char);
            state = 15; // ret fn 15
        }
        // error
        return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);

    case 15:
        flag = false;
        while (lexer->fp && isLetter_a2z(lexer->curr_char))
        {
            if (flag)
                append(lexeme, lexer->curr_char);
            getNextCharacter(lexer);
            flag = true;
        }

        return init_Token(TK_RUID, lexeme, lexer->lineNumber, lexer->charNumber);
    }
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
                    return init_Token(TK_ASSIGNOP, lexeme, lexer->lineNumber, lexer->charNumber);
                }

                // error
                return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);
            }

            // error
            return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);
        }
        if (lexer->curr_char == '=')
        {
            append(lexeme, lexer->curr_char);
            return init_Token(TK_LE, lexeme, lexer->lineNumber, lexer->charNumber);
        }

        return init_Token(TK_LT, lexeme, lexer->lineNumber, lexer->charNumber);
    }
    if (lexer->curr_char == '>')
    {
        getNextCharacter(lexer);

        if (lexer->curr_char == '=')
        {
            append(lexeme, lexer->curr_char);
            return init_Token(TK_GE, lexeme, lexer->lineNumber, lexer->charNumber);
        }
        return init_Token(TK_GT, lexeme, lexer->lineNumber, lexer->charNumber);
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
                return init_Token(TK_AND, lexeme, lexer->lineNumber, lexer->charNumber);
            }

            // error
            return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);
        }

        // error
        return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);
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
                return init_Token(TK_OR, lexeme, lexer->lineNumber, lexer->charNumber);
            }

            // error
            return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);
        }

        // error
        return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);
    }

    if (lexer->curr_char == '=')
    {
        getNextCharacter(lexer);

        if (lexer->curr_char == '=')
        {
            append(lexeme, lexer->curr_char);
            return init_Token(TK_EQ, lexeme, lexer->lineNumber, lexer->charNumber);
        }

        // error
        return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);
    }

    if (lexer->curr_char == '!')
    {
        getNextCharacter(lexer);

        if (lexer->curr_char == '=')
        {
            append(lexeme, lexer->curr_char);
            return init_Token(TK_NE, lexeme, lexer->lineNumber, lexer->charNumber);
        }

        // error
        return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);
    }

    // NOTE: to be removed, comments needn't be tokenized, simply skipped
    if (lexer->curr_char == '%')
        return init_Token(TK_COMMENT, lexeme, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '[')
        return init_Token(TK_SQL, lexeme, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == ']')
        return init_Token(TK_SQR, lexeme, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == ',')
        return init_Token(TK_COMMA, lexeme, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == ';')
        return init_Token(TK_SEM, lexeme, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == ':')
        return init_Token(TK_COLON, lexeme, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '.')
        return init_Token(TK_DOT, lexeme, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '(')
        return init_Token(TK_OP, lexeme, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == ')')
        return init_Token(TK_CL, lexeme, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '+')
        return init_Token(TK_PLUS, lexeme, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '-')
        return init_Token(TK_MINUS, lexeme, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '*')
        return init_Token(TK_MUL, lexeme, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '/')
        return init_Token(TK_DIV, lexeme, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '~')
        return init_Token(TK_NOT, lexeme, lexer->lineNumber, lexer->charNumber);

    // error --> should never occur here
    return init_Token(TK_ILLEGAL, lexeme, lexer->lineNumber, lexer->charNumber);
}

Token tokenize(Lexer lexer)
{
    Token tk;
    getNextCharacter(lexer); // TODO: check via boolean

    // whitespaces
    if (lexer->curr_char == ' ' || lexer->curr_char == '\t')
        return tokenize(lexer);
    // eof
    if (lexer->curr_char == '\0')
    {
        _closeFile(lexer);
        return -1;
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
    return init_Token(TK_ILLEGAL, illegal, lexer->lineNumber, lexer->charNumber);
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

    // error handling
    if (feof(lexer->fp))
        _closeFile(lexer);
    else if (fr != BUFFER_SIZE)
    {
        // file reading error
        if (ferror(lexer->fp))
        {
            sprintf(err_text, "Error while reading file: %s", lexer->filename);
            error(err_text);
            exit(1);
        }
    }
    clearerr(lexer->fp);

    if (lexer->BUFF_NUM == 1)
        lexer->buffp1 = 0;
    else
        lexer->buffp2 = 0;
}

void _closeFile(Lexer lexer)
{
    if (fclose(lexer->fp) != 0)
    {
        char err_text[300];
        // sprintf(err_text, "Error in closing file: %s", strerror(errno));
        sprintf(err_text, "Error in closing file: %s", lexer->filename);
        error(err_text);
        exit(1);
    }

    lexer->fp = NULL;
}