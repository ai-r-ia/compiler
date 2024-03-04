/*
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/

#include <stdlib.h>
#include "parser.h"
#include "printers.h"
#include "symbol_table.h"

Parser init_parser(char *lexer_filename)
{
    Grammar grammar = init_grammar("grammar.txt");
    populateFirst(grammar);
    populateFollow(grammar);
    info("FIRST and FOLLOW sets automated");
    populateParseTable(grammar);
    info("Parse Table constructed");

    Parser parser = (Parser)malloc(sizeof(struct parser));
    parser->currentNode = NULL;
    parser->position = 0;
    parser->lexer = init_lexer(lexer_filename);
    parser->grammar = grammar;
    parser->noError = true;

    parser->stack = init_vector(TOKEN);
    Token eo_stack = init_token(EO_STACK, char_to_string("$"), "S", -1, -1);
    push_back(parser->stack, eo_stack);

    return parser;
}

bool isKeywordSynToken(String string)
{
    for (int i = 0; i < 17; i++) // NOTE: length hard-coded
    {
        String fromList = char_to_string(keyword_syn_token_list[i]);
        if (compare(string, fromList))
            return true;
    }
    return false;
}

// ALGORITHM FOR PARSING
/*Let 𝑎 be the first symbol in 𝑤
Let 𝑋be the symbol at the top of the stack
while 𝑋≠ $:
    if 𝑋== 𝑎:
        pop the stack and advance the input
    else if 𝑋 is a terminal or 𝑀[𝑋, 𝑎] is an error entry:
        error
    else if 𝑀[𝑋, 𝑎] == 𝑋→ 𝑌1𝑌2… 𝑌𝑘:
        output the production
        pop the stack
        push 𝑌𝑘𝑌𝑘−1… 𝑌1 onto the stack
    𝑋← top stack symbol*/

TreeNode parseInputSourceCode(char *testcaseFile)
{
    Parser parser = init_parser(testcaseFile);

    char error_msg[200];
    SymbolTable symbolTable = init_table();

    Vector parseTable = parser->grammar->parseTable;

    Rule start_symbol = get(parser->grammar->rules, 0);

    // Pushing start symbol of the grammar into the stack
    TreeNode tree = init_treenode(start_symbol->NT);
    tokenToChildren(tree, start_symbol->derivables);

    TreeNode currentParent = tree;
    push_back(parser->stack, start_symbol->NT);

    parser->currentNode = getNextToken(parser->lexer);
    Token top_of_stack = (Token)top(parser->stack);

    while (top_of_stack->type != EO_STACK)
    {
        if (!parser->currentNode)
            break;
        printf("current: %s, type: %s\n", parser->currentNode->lexeme_str->text, token_type_list[parser->currentNode->type]);
        printf("STACK: ");
        printVector(parser->stack);
        printf("\n\n");
        if (compare(char_to_string(token_type_list[parser->currentNode->type]), top_of_stack->lexeme_str))
        {
            updateTerminalInTree(tree, parser->currentNode);
            if (!isSymbol(parser->currentNode->lexeme_str->text[0]))
                insert_item(symbolTable, parser->currentNode->lexeme_str, parser->currentNode);
            else if (isSymbolTableOperator(parser->currentNode->lexeme_str))
                insert_item(symbolTable, parser->currentNode->lexeme_str, parser->currentNode);
            pop_back(parser->stack);
            parser->currentNode = getNextToken(parser->lexer);
        }
        else // error-recovery
        {
            parser->noError = false;
            if (top_of_stack->type == TERMINAL)
            {

                if (parser->currentNode->type == TK_ILLEGAL) //  lexical errors
                {
                    char *error_msg_tk = parser->currentNode->error_msg;
                    sprintf(error_msg, "Line %2ld Error: %s", parser->currentNode->line_num, error_msg_tk);
                    error(error_msg);
                    parser->currentNode = getNextToken(parser->lexer);
                }

                else
                {
                    char err_terminal[100];
                    sprintf(err_terminal, "Line %2ld Error: The token %s for lexeme %s  does not match with the expected token %s",
                            parser->currentNode->line_num,
                            token_type_list[parser->currentNode->type],
                            parser->currentNode->lexeme_str->text,
                            top_of_stack->lexeme_str->text);
                    error(err_terminal);
                    pop_back(parser->stack);
                    top_of_stack = top(parser->stack);
                }
                continue;
            }

            Vector tableRow = (Vector)get(parseTable, top_of_stack->type);
            Rule rule = (Rule)get(tableRow, parser->currentNode->type);

            if (parser->currentNode->type == TK_ILLEGAL || rule->NT->type == SYN || rule->NT->type == ERROR)
            {
                // error recovery mechanism: Panic-Mode Recovery
                /*If the parser looks up entry M[A,a] and finds that it is blank/error, the input symbol a is skipped.
                    If the entry is syn, then the nonterminal on top of the stack is popped.*/

                // printf("error lexeme: %s, type: %s line: %d \n", parser->currentNode->lexeme_str->text, token_type_list[parser->currentNode->type], parser->currentNode->line_num);
                if (parser->currentNode->type == TK_ILLEGAL) //  lexical errors
                {
                    char *error_msg_tk = parser->currentNode->error_msg;
                    sprintf(error_msg, "Line %2ld Error: %s", parser->currentNode->line_num, error_msg_tk);
                    error(error_msg);

                    parser->currentNode = getNextToken(parser->lexer);
                }
                else if (rule->NT->type == ERROR) // error entry in parse table
                {

                    // if (isKeywordSynToken(char_to_string(token_type_list[parser->currentNode->type])))
                    //     parser->currentNode = getNextToken(parser->lexer);

                    Vector firsts_tos = init_vector(TOKEN);
                    if (rule->NT->type != ERROR)
                        firsts_tos = get(parser->grammar->first, rule->NT->type);
                    while (!isKeywordSynToken(char_to_string(token_type_list[parser->currentNode->type])) &&
                           (rule->NT->type != SYN) &&
                           (rule->NT->type != FIRST_SYN))
                    //    && !contains(firsts_tos, parser->currentNode)) // special keyword check
                    {
                        parser->currentNode = getNextToken(parser->lexer);
                        if (parser->currentNode->type == TK_ILLEGAL) // lexical error
                        {
                            char *error_msg_tk = parser->currentNode->error_msg;
                            sprintf(error_msg, "Line %2ld Error: %s", parser->currentNode->line_num, error_msg_tk);
                            error(error_msg);

                            parser->currentNode = getNextToken(parser->lexer);
                        }
                        rule = (Rule)get(tableRow, parser->currentNode->type);
                        if (rule->NT->type != ERROR)
                            firsts_tos = get(parser->grammar->first, rule->NT->type);
                        printf("lexeme: %s, type: %s line: %ld ",
                               parser->currentNode->lexeme_str->text,
                               token_type_list[parser->currentNode->type],
                               parser->currentNode->line_num);

                        printf("---bool: %d \n", isKeywordSynToken(char_to_string(token_type_list[parser->currentNode->type])));
                    }

                    if (rule->NT->type == SYN)
                    {
                        pop_back(parser->stack);
                    }
                    else
                    {
                        do
                        {
                            pop_back(parser->stack);
                            top_of_stack = top(parser->stack);
                            if (top_of_stack->type == TERMINAL)
                                break;
                            tableRow = (Vector)get(parseTable, top_of_stack->type);
                            if ((!tableRow))
                                continue;
                            rule = (Rule)get(tableRow, parser->currentNode->type);
                            if (rule->NT->type == SYN)
                            {
                                pop_back(parser->stack);
                                break;
                            }
                            if (rule->NT->type != ERROR)
                                firsts_tos = get(parser->grammar->first, rule->NT->type);
                            else
                                continue;
                        } while (!contains(firsts_tos, parser->currentNode));
                    }

                    sprintf(error_msg, "Line %2ld Error: Invalid token %s encountered with value %s stack top %s",
                            parser->currentNode->line_num,
                            token_type_list[parser->currentNode->type],
                            parser->currentNode->lexeme_str->text,
                            top_of_stack->lexeme_str->text);
                    error(error_msg);

                    // if (!contains(firsts_tos, parser->currentNode))
                    parser->currentNode = getNextToken(parser->lexer);
                }
                else if (rule->NT->type == SYN)
                {

                    pop_back(parser->stack);

                    sprintf(error_msg, "Line %2ld Error: Invalid token %s encountered with value %s stack top %s",
                            parser->currentNode->line_num,
                            token_type_list[parser->currentNode->type],
                            parser->currentNode->lexeme_str->text,
                            top_of_stack->lexeme_str->text);
                    error(error_msg);
                    top_of_stack = top(parser->stack);
                }
            }
            else if (rule)
            {
                // printRule(rule);
                addToTree(currentParent, rule);
                pop_back(parser->stack);

                for (int i = rule->derivables->size - 1; i > -1; i--)
                {
                    Token tk = (Token)get(rule->derivables, i);
                    Token new_tk = NULL;
                    new_tk = copy_token(new_tk, tk);
                    if (!compare(tk->lexeme_str, char_to_string("#")))
                        push_back(parser->stack, new_tk);
                }
            }
            else
            {
                traceback("undefined rule");
            }
        }
        top_of_stack = top(parser->stack);
    }

    if (parser->noError)
        saveParseTree(tree, 0);
    else
        info("Parse tree could not be generated");
    return tree;
}
