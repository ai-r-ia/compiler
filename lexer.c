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
    lexer->state = 0;
    // _closeFile(lexer);
    return lexer;
}

// void loadBuffer(Lexer lexer, String data)
// {
//     char *buffer;

//     if (lexer->BUFF_NUM == 2)
//     {
//         lexer->BUFF_SIZE1 = data->size + 1;
//         buffer = lexer->buff1;
//     }
//     else
//     {
//         lexer->BUFF_SIZE2 = data->size + 1;
//         buffer = lexer->buff2;
//     }

//     for (int i = 0; i < data->size; i++)
//     {
//         buffer[i] = data->text[i];
//     }

//     buffer[data->size] = '\0';
//     if (lexer->BUFF_NUM == 2)
//         lexer->buff1 = buffer;
//     else
//         lexer->buff2 = buffer;
// }

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
18: ret tk_num
19: if [0-9] after 17
20: if [0-9] after 19
21: if [E]
22: if [+|-]
23: if [0-9] after 22
24: if [0-9] after 23
25: ret tk_rnum
*/
Token get_numeric_tk(Lexer lexer)
{
    String lexeme = init_str();
    append(lexeme, lexer->curr_char);
    while (1)
    {
        switch (lexer->state)
        {
        case 2:
            lexer->curr_char = getNextCharacter(lexer);
            if (lexer->curr_char == '.')
                lexer->state = 17;
            if (!isDigit_0_9(lexer->curr_char) && lexer->curr_char != '.')
                lexer->state = 18;
            if (isDigit_0_9(lexer->curr_char) || lexer->curr_char == '.')
                append(lexeme, lexer->curr_char);
            break;
        case 17:
            lexer->curr_char = getNextCharacter(lexer);
            if (isDigit_0_9(lexer->curr_char))
            {
                lexer->state = 19;
                append(lexeme, lexer->curr_char);
            }
            else
                lexer->state = 505; // error
            break;
        case 18:
            return init_Token(TK_NUM, lexeme, lexer->lineNumber, lexer->charNumber);
        case 19:
            lexer->curr_char = getNextCharacter(lexer);
            if (isDigit_0_9(lexer->curr_char))
            {
                lexer->state = 20;
                append(lexeme, lexer->curr_char);
            }
            else
                lexer->state = 505; // error
            break;
        case 20:
            lexer->curr_char = getNextCharacter(lexer);
            if (lexer->curr_char == 'E')
            {
                lexer->state = 21;
                append(lexeme, lexer->curr_char);
            }
            else
                lexer->state = 25; // error
            break;
        case 21:
            lexer->curr_char = getNextCharacter(lexer);
            if ((lexer->curr_char == '+') || (lexer->curr_char == '-'))
            {
                lexer->state = 22;
                append(lexeme, lexer->curr_char);
            }
            else if (isDigit_0_9(lexer->curr_char))
            {
                lexer->state = 23;
                append(lexeme, lexer->curr_char);
            }
            else
                lexer->state = 505; // error
            break;

        case 23:
            lexer->curr_char = getNextCharacter(lexer);
            if (isDigit_0_9(lexer->curr_char))
            {
                lexer->state = 24;
                append(lexeme, lexer->curr_char);
            }
            else
                lexer->state = 505; // error
            break;
        case 24: // TODO: check if this can be skipped
            lexer->state = 25;
            break;
        case 25:
            return init_Token(TK_RNUM, lexeme, lexer->lineNumber, lexer->charNumber);
        case 505:

            break;
            // lexical error TODO:
        }
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

    if (isLetter_b2d(lexer->curr_char))
        lexer->state = 4;
    else if (lexer->curr_char == 'a' || isLetter_e2z(lexer->curr_char))
        lexer->state = 5;
    else if (lexer->curr_char == '_')
        lexer->state = 10;
    else if (lexer->curr_char == '#')
        lexer->state = 14;
    else
        error("Anamoly in char received at get_char_tk.");

    switch (lexer->state)
    {
    case 4:
        getNextCharacter(lexer);
        if (isDigit_2_7(lexer->curr_char))
        {
            append(lexeme, lexer->curr_char);
            lexer->state = 7; // ret fn 7
        }
        if (isLetter_a2z(lexer->curr_char))
        {
            append(lexeme, lexer->curr_char);
            lexer->state = 5; // ret fn 5
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
                lexer->state = 8; // ret fn 8
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
            lexer->state = 11; // ret fn 11
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
                lexer->state = 12; // ret fn 12
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
            lexer->state = 15; // ret fn 15
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

// Token tokenize(Lexer lexer)
// {
//     lexer->curr_char = getNextCharacter(lexer);

//     // Check whether EOF
//     if (lexer->curr_char == '\0') // TODO: check
//     {
//         _closeFile(lexer);
//         return iToken(TK_EOF, NULL, NULL, lexer->lineNumber, lexer->charNumber);
//     }

//     // Ignore whitespaces
//     if (lexer->curr_char == ' ' || lexer->curr_char == '\t')
//     {
//         return tokenize(lexer);
//     }

//     // Check for char related tokens
//     if (isLetter_e2z(lexer->curr_char) || isLetter_b2d(lexer->curr_char) || lexer->curr_char == '_' || lexer->curr_char == '#' || lexer->curr_char == 'a')
//     {
//         return get_char_tk(lexer, lexer->curr_char);
//     }

//     // Check for numeric tokens
//     if (isDigit(lexer->curr_char))
//     {
//         return get_numeric_tk(lexer, lexer->curr_char);
//     }

//     Token token = get_symbol_tk(lexer, lexer->curr_char);

//     if (token->type == TK_ILLEGAL)
//     {
//         char errorString[200];
//         sprintf(errorString, "Line %d - Error: Illegal character input: '%c' at %d:%d", lexer->lineNumber, lexer->curr_char, lexer->lineNumber, lexer->charNumber);
//         error(errorString);
//     }

//     return token;
// }

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