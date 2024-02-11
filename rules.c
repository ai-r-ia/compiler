#include "whole_include.h"

Rule init_rule(Token NT)
{
    Rule rule = (Rule)malloc(sizeof(struct rule));
    rule->NT = NT;
    rule->derivables = init_vector(TOKEN);
    return rule;
}

Grammar init_grammar(char *filename)
{
    Grammar grammar = (Grammar)malloc(sizeof(struct grammar));
    grammar->filename = filename;
    grammar->rules = init_vector(RULE);
    _loadGrammar(grammar);

    printRule(get(grammar->rules, 0));

    return grammar;
}

void printRule(Rule rule)
{
    printf("%s --> ", ((rule->NT)->lexeme_str)->text);
    printVector(rule->derivables);
    printf("\n");
}

// private functions

void _loadGrammar(Grammar grammar)
{

    FILE *fp = fopen(grammar->filename, "r");
    char err_text[300];

    if (fp == NULL)
    {
        sprintf(err_text, "Error in opening file: %s", grammar->filename);
        error(err_text);
        exit(1);
    }

    // eof reached
    if (!fp)
    {
        error("grammar file is closed");
        return;
    }

    size_t fr;
    char *buff = (char *)malloc(sizeof(char) * (GRAMMAR_LENGTH + 1));

    memset(buff, '\0', GRAMMAR_LENGTH + 1);
    fr = fread(buff, 1, GRAMMAR_LENGTH, fp);

    // Loading rules
    int line_num = 0;
    char *line = strtok(strdup(buff), "\n");
    while (line)
    {
        line_num++;

        // char *copy = (char *)malloc(strlen(line) + 1);
        // if (copy == NULL)
        // {
        //     printf("fucked up");
        // }
        // strcpy(copy, line);

        // char *tokens = strtok_r(copy, "-");

        char *rest = line;

        char *tokens = strtok_r(rest, " ", &rest);
        int flag = 0;
        Rule rule;
        while (tokens)
        {
            if (flag == 0)
            {
                // printf("LHS %s \n", tokens);

                String non_terminal = init_str();
                append(non_terminal, tokens[0]);
                int type = _getNonTerminal(non_terminal);
                if (type == -1)
                {
                    error("Non terminal type does not exist.");
                    exit(1);
                }

                Token nonTerminal = init_Token(type, char_to_string(tokens), tokens, line_num, 1);
                rule = init_rule(nonTerminal);

                flag = 1;
            }
            else
            {
                // printf("RHS %s \n", tokens);

                Token terminal = init_Token(5, char_to_string(tokens), tokens, line_num, 1);
                push_back(rule->derivables, terminal);
            }
            tokens = strtok(NULL, "-");
            push_back(grammar->rules, rule);
        }

        line = strtok(NULL, "\n");
    }

    // error handling
    if (feof(fp))
    {
        if (fclose(fp) != 0)
        {
            error("Error in closing grammar file");
            exit(1);
        }

        fp = NULL;
    }
}

int _getNonTerminal(String nonTerminal)
{

    for (int i = 0; i < 8; i++)
    {
        if (compare(char_to_string(grammarTokenKindString[i]), nonTerminal))
        {
            return i;
        }
    }
    return -1;
}