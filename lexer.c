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

    lexer->buff_begin1 = 0;
    lexer->buff_begin2 = 0;
    lexer->buffp1 = 0;
    lexer->buffp2 = 0;
    lexer->lineNumber = 1;
    lexer->charNumber = 1;

    _closeFile(lexer);
    return lexer;
}

void loadBuffer(Lexer lexer, String data)
{
    char *buffer;

    if (lexer->BUFF_NUM == 1)
    {
        lexer->BUFF_SIZE1 = data->size + 1;
        buffer = lexer->buff1;
    }
    else
    {
        lexer->BUFF_SIZE2 = data->size + 1;
        buffer = lexer->buff2;
    }

    for (int i = 0; i < data->size; i++)
    {
        buffer[i] = data->text[i];
    }

    buffer[data->size] = '\0';
    if (lexer->BUFF_NUM == 1)
        lexer->buff1 = buffer;
    else
        lexer->buff2 = buffer;
}

char getNextCharacter(Lexer lexer)
{

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

void _readFile(Lexer lexer)
{
    int size = lexer->BUFF_SIZE1 + lexer->BUFF_SIZE2;

    for (int i = 0; i < size; i++)
    {
        char c = fgetc(lexer->fp);
        if (ferror(lexer->fp))
        {
            char err_text[300];
            sprintf(err_text, "Error while reading file: %s", lexer->filename);
            error(err_text);
            exit(1);
        }
        clearerr(lexer->fp);
        if (i < lexer->BUFF_SIZE1)
            lexer->buff1[i] = c;
        else
            lexer->buff2[i - lexer->BUFF_SIZE1] = c;
    }

    lexer->buff1[lexer->BUFF_SIZE1] = '\0';
    lexer->buff2[lexer->BUFF_SIZE2] = '\0';
}

void _closeFile(Lexer lexer)
{
    if (fclose(lexer->fp) != 0)
    {
        char err_text[300];
        sprintf(err_text, "Error in closing file: %s", strerror(errno));
        // sprintf(err_text, "Error in closing file: %s", lexer->filename);
        error(err_text);
        exit(1);
    }

    lexer->fp = NULL;
}