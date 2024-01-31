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

    lexer->all_input_read = false;
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
        lexer->prevLineChar = lexer->curr_char; // TODO: check if this is needed
        lexer->charNumber = 1;
    }
    return res;
}

// Token tokenize(Lexer lexer){
//     lexer->curr_char = getNextCharacter(lexer);

// // Check whether EOF
// if (lexer->curr_char == -1)
// {
//     _closeFile(lexer);
//     return iToken(ENDOFFILE, NULL, NULL, lexer->lineNumber, lexer->charNumber);
// }

// // Ignore whitespaces
// if (lexer->curr_char == ' ' || lexer->curr_char == '\t')
// {
//     return tokenize(lexer);
// }

// // Check for String literal
// if (isChar(lexer->curr_char) || lexer->curr_char == '_')
// {
//     return getID(lexer, lexer->curr_char);
// }

// // Check for Integer or Decimal number
// if (isDigit(lexer->curr_char))
// {
//     return getNUM(lexer, lexer->curr_char);
// }

// Token token = getSymbol(lexer, lexer->curr_char);

// if (token->type == TK_ILLEGAL)
// {
//     char errorString[200];
//     sprintf(errorString, "Line %d : Error: Bad character input: '%c' at %d:%d", lexer->lineNumber, lexer->curr_char, lexer->lineNumber, lexer->charNumber);
//     error(errorString);
// }

// return token;
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

    size_t fr;

    if (lexer->BUFF_NUM == 1)
        fr = fread(lexer->buff1, 1, lexer->BUFF_SIZE1, lexer->fp);
    else
        fr = fread(lexer->buff2, 1, lexer->BUFF_SIZE2, lexer->fp);

    // error handling
    if (fr != BUFFER_SIZE)
    {
        char err_text[300];

        // eof reached
        if (feof(lexer->fp) && !lexer->all_input_read)
        {
            if (lexer->BUFF_NUM == 1)
                lexer->buff1[fr + 1] = '\0';
            else
                lexer->buff2[fr + 1] = '\0';
            lexer->all_input_read = true;
            // sprintf(err_text, "Error while reading file: %s. Unexpected end of file", lexer->filename);
            // error(err_text);
            info("EOF reached");
            // exit(1);
        }

        // file reading error
        else if (ferror(lexer->fp))
        {
            sprintf(err_text, "Error while reading file: %s", lexer->filename);
            error(err_text);
            exit(1);
        }

        else if (lexer->all_input_read)
        {
            info("All input has already been read.");
        }
    }
    clearerr(lexer->fp);

    if (lexer->BUFF_NUM == 1)
    {
        lexer->buffp1 = 0;
        lexer->buff1[lexer->BUFF_SIZE1] = '\0';
    }
    else
    {
        lexer->buffp2 = 0;
        lexer->buff2[lexer->BUFF_SIZE2] = '\0';
    }
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