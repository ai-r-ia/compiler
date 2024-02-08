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

int getKeyword(String word)
{
    for (int i = 0; i < 28; i++)
    {
        if (compare(char_to_string(keyword_type_list[i]), word))
            return i;
    }

    return -1;
}

Token error_function(Lexer lexer, String lexeme, enum TOKEN_TYPE type, bool others)
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
        value = (char *)malloc(sizeof(char));
        value = lexeme->text;
        break;
    default:
        error("No coherent type provided to 'error_function'.");
        break;
    }

    if ((lexer->curr_char == ' ') || (lexer->curr_char == '\t') || (lexer->curr_char == '\n') || isSymbol(lexer->curr_char) || (lexer->curr_char == '\0') || others)
    {
        retract(lexer, lexeme);
        return init_Token(type, lexeme, value, lexer->lineNumber, lexer->charNumber);
    }

    while (((lexer->curr_char != ' ') && (lexer->curr_char != '\t') && (lexer->curr_char != '\n') && (lexer->curr_char != '\0') && (!isSymbol(lexer->curr_char))))
    {
        append(lexeme, lexer->curr_char);
        getNextCharacter(lexer);
    }

    retract(lexer, lexeme);
    return init_Token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
}

char getNextCharacter(Lexer lexer)
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
    if (lexer->fwd_ptr != '\0')
        lexer->fwd_ptr--;

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

    if (lexer->curr_char == '.')
    {
        append(lexeme, lexer->curr_char);
        return get_tk_rnum1(lexer, lexeme);
    }

    retract(lexer, lexeme);
    return error_function(lexer, lexeme, TK_NUM, true);
}

Token get_tk_rnum1(Lexer lexer, String lexeme)
{

    getNextCharacter(lexer);
    if (isDigit_0_9(lexer->curr_char))
    {
        append(lexeme, lexer->curr_char);
        return get_tk_rnum2(lexer, lexeme);
    }
    // error
    retract(lexer, lexeme);
    return error_function(lexer, lexeme, TK_NUM, true);
}

Token get_tk_rnum2(Lexer lexer, String lexeme)
{

    getNextCharacter(lexer);
    if (isDigit_0_9(lexer->curr_char))
    {
        append(lexeme, lexer->curr_char);
        return get_tk_rnum3(lexer, lexeme);
    }
    // error
    return error_function(lexer, lexeme, TK_ILLEGAL, true);
}

Token get_tk_rnum3(Lexer lexer, String lexeme)
{

    getNextCharacter(lexer);
    if (lexer->curr_char == 'E')
    {
        append(lexeme, lexer->curr_char);
        return get_tk_rnum4(lexer, lexeme);
    }
    // error
    return error_function(lexer, lexeme, TK_RNUM, true);
}

Token get_tk_rnum4(Lexer lexer, String lexeme)
{

    getNextCharacter(lexer);
    if ((lexer->curr_char == '+') || (lexer->curr_char == '-'))
    {
        append(lexeme, lexer->curr_char);
        return get_tk_rnum5(lexer, lexeme);
    }
    else if (isDigit_0_9(lexer->curr_char))
    {
        append(lexeme, lexer->curr_char);
        return get_tk_rnum6(lexer, lexeme);
    }
    // error
    return error_function(lexer, lexeme, TK_ILLEGAL, true);
}

Token get_tk_rnum5(Lexer lexer, String lexeme)
{

    getNextCharacter(lexer);
    if (isDigit_0_9(lexer->curr_char))
    {
        append(lexeme, lexer->curr_char);
        return get_tk_rnum6(lexer, lexeme);
    }

    // error
    retract(lexer, lexeme);
    return error_function(lexer, lexeme, TK_ILLEGAL, true);
}

Token get_tk_rnum6(Lexer lexer, String lexeme)
{

    getNextCharacter(lexer);
    if (isDigit_0_9(lexer->curr_char))
    {
        append(lexeme, lexer->curr_char);
        getNextCharacter(lexer);
        return error_function(lexer, lexeme, TK_RNUM, true);
    }
    // error
    return error_function(lexer, lexeme, TK_ILLEGAL, true);
}

/*
    This function handles character-based tokens.
    It checks the current character and determines the appropriate state to transition to.

    There are 4 states in this function:
    State 4: If the current character is in the range [b-d]
    State 5: If the current character is 'a' or in the range [e-z], or any letter in the range [a-z] and checks for a keyword
    State 10: If the current character is '_'
    State 14: If the current character is '#'

    If the current character is not in the specified ranges, it is considered an illegal character.
    If the current character is '_', it transitions to state 10.
    If the current character is '#', it transitions to state 14.
*/
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
    retract(lexer, lexeme);
    return init_Token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
}

/*
    This function handles state 4 of character-based tokens.
    If the current character is in the range [b-d], it transitions to state 7 or state 5.
    If the current character is a letter in the range [a-z], it transitions to state 5.
    Otherwise, it is considered an illegal character.
*/
Token after_b2d(Lexer lexer, String lexeme)
{

    getNextCharacter(lexer);

    if (isDigit_2_7(lexer->curr_char))
    {
        append(lexeme, lexer->curr_char);
        return get_tk_id2(lexer, lexeme); // ret fn 7
    }
    if (isLetter_a2z(lexer->curr_char))
    {
        append(lexeme, lexer->curr_char);
        return get_tk_fieldid(lexer, lexeme);
    }
    // error
    retract(lexer, lexeme);
    return init_Token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
}

/*
    This function handles state 5 of character-based tokens.
    If the current character is a letter in the range [a-z], it transitions to state 5.
    Otherwise, it is considered an illegal character.
*/
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

    if ((lexer->curr_char == ' ') || (lexer->curr_char == '\t') || (lexer->curr_char == '\n') || isSymbol(lexer->curr_char) || (lexer->curr_char == '\0'))
    {
        int keyword = getKeyword(lexeme);
        if (keyword != -1)
        {
            retract(lexer, lexeme);
            return init_Token(keyword_token_value[keyword], lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        }
    }

    return error_function(lexer, lexeme, TK_FIELDID, true);
}

/*
    This function handles state 7 of character-based tokens.
    If the current character is in the range [2-7], it transitions to state 8.
    Otherwise, it is considered an illegal character.
*/
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

    return error_function(lexer, lexeme, TK_FIELDID, true);
}

/*
    This function handles state 8 of character-based tokens.
    If the current character is a letter in the range [a-z], it transitions to state 11.
    Otherwise, it is considered an illegal character.
*/
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
    return error_function(lexer, lexeme, TK_ID, true);
}

Token get_tk_funid0(Lexer lexer, String lexeme)
{

    getNextCharacter(lexer);
    if (isLetter_a2z_A2Z(lexer->curr_char))
    {
        append(lexeme, lexer->curr_char);
        return get_tk_funid1(lexer, lexeme); // ret fn 11
    }
    // error
    retract(lexer, lexeme);
    return init_Token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
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

        if (isDigit_0_9(lexer->curr_char))
        {
            append(lexeme, lexer->curr_char);
            return get_tk_funid3(lexer, lexeme);
            ; // ret fn 12
        }
        flag = true;
    }
    if ((lexer->curr_char == ' ') || (lexer->curr_char == '\t') || (lexer->curr_char == '\n') || isSymbol(lexer->curr_char) || (lexer->curr_char == '\0'))
    {
        int keyword = getKeyword(lexeme);
        if (keyword_token_value[keyword] == 17)
        {
            retract(lexer, lexeme);
            return init_Token(TK_MAIN, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        }
    }

    return error_function(lexer, lexeme, TK_FUNID, true);
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

    return error_function(lexer, lexeme, TK_FUNID, true);
}

Token get_tk_ruid0(Lexer lexer, String lexeme)
{

    getNextCharacter(lexer);
    if (isLetter_a2z(lexer->curr_char))
    {
        append(lexeme, lexer->curr_char);
        return get_tk_ruid1(lexer, lexeme); // ret fn 15
    }
    // error
    return init_Token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
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

    return error_function(lexer, lexeme, TK_RUID, false);
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
                    return init_Token(TK_ASSIGNOP, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
                }

                // error
                retract(lexer, lexeme);
                return init_Token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
            }

            // error
            retract(lexer, lexeme);

            return init_Token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        }
        if (lexer->curr_char == '=')
        {
            append(lexeme, lexer->curr_char);
            return init_Token(TK_LE, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        }

        retract(lexer, lexeme);

        return init_Token(TK_LT, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
    }
    if (lexer->curr_char == '>')
    {
        getNextCharacter(lexer);

        if (lexer->curr_char == '=')
        {
            append(lexeme, lexer->curr_char);
            return init_Token(TK_GE, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        }
        retract(lexer, lexeme);

        return init_Token(TK_GT, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
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
                return init_Token(TK_AND, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
            }

            // error
            retract(lexer, lexeme);

            return init_Token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        }

        // error
        retract(lexer, lexeme);

        return init_Token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
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
                return init_Token(TK_OR, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
            }

            // error
            retract(lexer, lexeme);

            return init_Token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        }

        // error
        retract(lexer, lexeme);

        return init_Token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
    }

    if (lexer->curr_char == '=')
    {
        getNextCharacter(lexer);

        if (lexer->curr_char == '=')
        {
            append(lexeme, lexer->curr_char);
            return init_Token(TK_EQ, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        }

        // error
        retract(lexer, lexeme);

        return init_Token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
    }

    if (lexer->curr_char == '!')
    {
        getNextCharacter(lexer);

        if (lexer->curr_char == '=')
        {
            append(lexeme, lexer->curr_char);
            return init_Token(TK_NE, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
        }

        // error
        retract(lexer, lexeme);

        return init_Token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
    }

    // NOTE: to be removed, comments needn't be tokenized, simply skipped
    if (lexer->curr_char == '%')
    {
        while (lexer->curr_char != '\n')
        {
            getNextCharacter(lexer);
            append(lexeme, lexer->curr_char);
        }
    }
    return init_Token(TK_COMMENT, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '[')
        return init_Token(TK_SQL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == ']')
        return init_Token(TK_SQR, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == ',')
        return init_Token(TK_COMMA, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == ';')
        return init_Token(TK_SEM, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == ':')
        return init_Token(TK_COLON, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '.')
        return init_Token(TK_DOT, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '(')
        return init_Token(TK_OP, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == ')')
        return init_Token(TK_CL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '+')
        return init_Token(TK_PLUS, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '-')
        return init_Token(TK_MINUS, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '*')
        return init_Token(TK_MUL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '/')
        return init_Token(TK_DIV, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    if (lexer->curr_char == '~')
        return init_Token(TK_NOT, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);

    // error --> should never occur here
    retract(lexer, lexeme);

    return init_Token(TK_ILLEGAL, lexeme, lexeme->text, lexer->lineNumber, lexer->charNumber);
}

Token tokenize(Lexer lexer)
{
    getNextCharacter(lexer);

    // whitespaces
    if (lexer->curr_char == ' ' || lexer->curr_char == '\t' || lexer->curr_char == '\n')
        return tokenize(lexer);

    // eof
    if (lexer->curr_char == '\0')
    {
        _closeFile(lexer);
        return NULL; // TODO: check if tk_eof needed
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
    return init_Token(TK_ILLEGAL, illegal, illegal->text, lexer->lineNumber, lexer->charNumber);
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
    // if (feof(lexer->fp))
    //     _closeFile(lexer);  //DEBUG:
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

// this is just a trial