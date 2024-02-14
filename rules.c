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

    // printf("%s --> ", ((Rule)get(grammar->rules, 1))->NT->lexeme_str->text);
    // printf("%s \n", ((Rule)get(grammar->rules, 1))->derivables);

    printRule(get(grammar->rules, 0));
    printRule(get(grammar->rules, 1));

    return grammar;
}

void printRule(Rule rule)
{
    printf("%s --> ", ((rule->NT)->lexeme_str)->text);
    // printVector(rule->derivables);
    for (int i = 0; i < rule->derivables->size; i++)
    {
        printf("%s ", (((Token)get(rule->derivables, i))->lexeme_str)->text);
    }
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
    Vector allRules = init_vector(RULE);
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

        char *tokens = strtok_r(rest, "~", &rest);
        int flag = 0;
        Rule rule;
        while (tokens)
        {
            if (flag == 0)
            {
                // printf("LHS %s \n", tokens);

                struct string non_terminal = *init_str();
                append(&non_terminal, tokens[0]);
                int type = _getNonTerminal(&non_terminal);
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
                // char* tok2 = tokens;
                // char * terms = strtok_r(tok2, "|", &tok2);

                // while(terms){
                //     terms = strtok_r(NULL, "\n", &tok2);
                // }
                Token terminal = init_Token(5, char_to_string(tokens), tokens, line_num, 1);

                push_back(rule->derivables, terminal);
                flag = 0;
            }

            tokens = strtok_r(NULL, "~", &rest);
            push_back(allRules, rule);
        }

        line = strtok(NULL, "\n");
    }

    grammar->rules = allRules;
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