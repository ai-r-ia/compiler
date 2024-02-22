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
    grammar->first = init_vector(VECTOR);
    grammar->follow = init_vector(VECTOR);
    grammar->nullable = (int *)malloc(sizeof(int) * TERMINAL);

    _loadGrammar(grammar);

    // for (int i = 0; i < grammar->rules->size; i++)
    // {
    //     printRule(get(grammar->rules, i));
    // }

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

    size_t i = 0;

    char curr = buff[i];
    while (curr != '\0')
    {
        if (curr == ' ' || curr == '\n')
        {
            curr = buff[++i];
            continue;
        }

        if (curr == '<')
        {
            String nonterm = init_str();
            curr = buff[++i];
            while (curr != '>')
            {
                append(nonterm, curr);
                curr = buff[++i];
            }
            curr = buff[++i];

            Token NT = init_Token(_matchNonTerminal(nonterm), nonterm, NULL, 0, 0);
            Rule rule = init_rule(NT);
            // printf("lhs %s ", nonterm->text);
            while (curr == ' ')
            {
                curr = buff[++i];
            }

            if (curr != '=')
            {
                error("Invalid Rule");
                exit(1);
            }
            curr = buff[++i];

            Vector rhs = init_vector(TOKEN);

            while (curr != '\n' && curr != '\0')
            {

                String term = init_str();

                while (curr == ' ')
                {
                    curr = buff[++i];
                }
                if (curr == '\n')
                {
                    continue;
                }
                // if non terminal
                if (curr == '<')
                {
                    curr = buff[++i];

                    while (curr != '>' && curr != '\n')
                    {
                        append(term, curr);
                        curr = buff[++i];
                    }

                    Token tk = init_Token(_matchNonTerminal(term), term, NULL, 0, 0);
                    // printf("non terminal %s ", term->text);
                    curr = buff[++i];
                    push_back(rhs, tk);
                }
                // if terminal
                else
                {
                    while (curr != '<' && curr != '\n' && curr != ' ')
                    {
                        append(term, curr);
                        curr = buff[++i];
                    }

                    Token tk = init_Token(TERMINAL, term, NULL, 0, 0);
                    // printf("terminal %s ", term->text);

                    push_back(rhs, tk);
                }
                rule->derivables = rhs;
                // curr = buff[++i];
                while (curr == ' ')
                {
                    curr = buff[++i];
                }
            }
            Token first = (Token)get(rule->derivables, 0);
            if (compare(first->lexeme_str, char_to_string("#")))
            {
                (grammar->nullable)[rule->NT->type] = 1;
            }
            push_back(grammar->rules, rule);
        }

        // else
        // {
        //     error("Invalid Rule, doesn't begin with non terminal.");
        //     exit(1);
        // }
        curr = buff[++i];
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

int _matchNonTerminal(String nonTerminal)
{

    for (int i = 0; i < TERMINAL; i++)
    {
        if (compare(char_to_string(grammarTokenKindString[i]), nonTerminal) == 1)
        {
            return i;
        }
    }
    return -1;
}

Vector getFirst(Token token, Grammar grammar)
{
    Vector first = init_vector(TOKEN);

    for (int i = 0; i < grammar->rules->size; i++)
    {
        Rule rule = get(grammar->rules, i);

        if (rule->NT->type != token->type)
            continue;

        Token tk = (Token)get(rule->derivables, 0);

        if (tk->type == TERMINAL)
        {
            if (!contains(first, tk))
                push_back(first, tk);
        }

        else
        {
            for (int j = 0; j < rule->derivables->size; j++)
            {
                tk = (Token)get(rule->derivables, j);
                if (tk->type == TERMINAL)
                {
                    if (!contains(first, tk))
                        push_back(first, tk);
                    break;
                }
                Vector tk_firsts = get(grammar->first, tk->type);

                for (int k = 0; k < tk_firsts->size; k++)
                {
                    Token token2 = (Token)get(tk_firsts, k);
                    if (!compare(token2->lexeme_str, char_to_string("#")) && !contains(first, token2))
                        push_back(first, token2);
                }
                if ((grammar->nullable)[tk->type] == 0)
                    break;
            }
        }
    }
    return first;
}

void populateFirst(Grammar grammar)
{
    // populating grammar first with empty vectors corresponding to index of each non terminal
    for (int i = 0; i < TERMINAL; i++)
    {
        Vector firstForNonTerminal = init_vector(TOKEN);
        push_back(grammar->first, firstForNonTerminal);
    }

    // add if terminal in beginning of rule for all non terminals(lhs)
    for (size_t j = 0; j < grammar->rules->size; j++)
    {

        Rule rule = get(grammar->rules, j);

        Token tk = get(rule->derivables, 0);

        if (tk->type == TERMINAL)
        {

            Vector firstOfNT = (Vector)get(grammar->first, rule->NT->type);

            if (!firstOfNT)
                firstOfNT = init_vector(TOKEN);

            if (!contains(firstOfNT, tk))
            {
                push_back(firstOfNT, tk);
            }
        }
    }

    // add first of non terminals for each non terminal in lhs
    bool nonTerminalAdded = true;

    while (nonTerminalAdded)
    {
        nonTerminalAdded = false;
        for (int j = 0; j < TERMINAL; j++)
        {
            Token tk = init_Token(j, char_to_string(grammarTokenKindString[j]), NULL, 0, 0);

            Vector firstOfRhsNT = getFirst(tk, grammar);

            Vector firstOfLhsNT = (Vector)get(grammar->first, j);

            for (size_t i = 0; i < firstOfRhsNT->size; i++)
            {
                if (!contains(firstOfLhsNT, (Token)get(firstOfRhsNT, i)))
                {
                    nonTerminalAdded = true;
                    push_back(firstOfLhsNT, (Token)get(firstOfRhsNT, i));
                }
            }
        }
    }
}

void populateFollow(Grammar grammar)
{
    // populating grammar follow with empty vectors corresponding to index of each non terminal
    for (int i = 0; i < TERMINAL; i++)
    {
        Vector followForNonTerminal = init_vector(TOKEN);
        push_back(grammar->follow, followForNonTerminal);
    }

    // adding stack symbol $ in follow set of start symbol
    Token stack_symbol = init_Token(EO_STACK, char_to_string("$"), "$", 0, 0);
    Vector start_vec = get(grammar->follow, ((Rule)get(grammar->rules, 0))->NT->type);
    push_back(start_vec, stack_symbol);

    for (int i = 0; i < TERMINAL; i++)
    {
        Token nonTerminal = init_Token(i, char_to_string(grammarTokenKindString[i]), grammarTokenKindString[i], 0, 0);
        Vector currFollow = get(grammar->follow, i);

        for (int r = 0; r < grammar->rules->size; r++)
        {
            Rule rule = (Rule)get(grammar->rules, r);
            Vector rhs = rule->derivables;

            for (int d = 0; d < rhs->size; d++)
            {
                Token tk = (Token)get(rhs, d);
                if (tk->type == nonTerminal->type)
                {

                    bool includeLhsFollow = false;
                    if (d == rhs->size - 1)
                        includeLhsFollow = true;
                    if (d < rhs->size - 1)
                    {
                        for (int k = d + 1; k < rhs->size; k++)
                        {
                            Token nextToken = (Token)get(rhs, k);
                            if (nextToken->type == TERMINAL)
                            {
                                if (!contains(currFollow, nextToken) && !compare(nextToken->lexeme_str, char_to_string("#")))
                                    push_back(currFollow, nextToken);
                                break;
                            }
                            Vector nextFirst = get(grammar->first, nextToken->type);
                            if ((grammar->nullable)[nextToken->type] && (k + 1 == rhs->size))
                                includeLhsFollow = true;

                            for (int j = 0; j < nextFirst->size; j++)
                            {
                                Token tk = (Token)get(nextFirst, j);
                                if (!contains(currFollow, tk) && !compare(tk->lexeme_str, char_to_string("#")))
                                    push_back(currFollow, tk);
                            }
                        }
                    }

                    if (includeLhsFollow)
                    {
                        Vector lhsFollow = (Vector)get(grammar->follow, rule->NT->type);
                        for (int j = 0; j < lhsFollow->size; j++)
                        {
                            Token tk = (Token)get(lhsFollow, j);
                            if (!contains(currFollow, tk) && !compare(tk->lexeme_str, char_to_string("#")))
                                push_back(currFollow, tk);
                        }
                    }
                }
            }
        }
    }
}