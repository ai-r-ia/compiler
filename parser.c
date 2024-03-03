#include <stdlib.h>
#include "parser.h"
#include "printers.h"
#include "symbol_table.h"

/*FirstAndFollow
ComputeFirstAndFollowSets (grammar G):
This function takes as input the grammar G, computes FIRST and FOLLOW information and populates appropriate data structure FirstAndFollow.
First and Follow set automation must be attempted, keeping in view the programming confidence of the team members and the available time with the teams.
If teams opt not to develop the module for computation of First and follow sets, the same can be computed manually and information be populated in the
data structure appropriately. However, all members of the team must understand that any new grammar rule for any new construct will then require their
expertise in computing FIRST and FOLLOW sets manually.

createParseTable(FirstAndFollow F, table T):
This function takes as input the FIRST and FOLLOW  information in F to populate the table T appropriately.

parseInputSourceCode(char *testcaseFile, table T):
This function takes as input the source code file and parses using the rules as per the predictive parse table T and
returns a parse tree. The function gets the tokens using lexical analysis interface and establishes the syntactic
structure of the input source code using rules in T. The function must report all errors appropriately (with line numbers)
 if the source code is syntactically incorrect. If the source code is correct then the token and all its relevant
 information is added to the parse tree. The start symbol of the grammar is the root of the parse tree and the tree
 grows as the syntax analysis moves in top down way. The function must display a message "Input source code is
  syntactically correct..........." for successful parsing.

printParseTree(parseTree PT, char *outfile):
This function provides an interface for observing the correctness of the creation of parse tree.
The function prints the parse tree in inorder in the file outfile.
The output is such that each line of the file outfile must contain the information corresponding to the
currently visited node of the parse tree in the following format

lexeme CurrentNode lineno tokenName valueIfNumber parentNodeSymbol isLeafNode(yes/no) NodeSymbol

The lexeme of the current node is printed when it is the leaf node else a dummy string of characters "‐‐‐‐" is printed.
The line number is one of the information collected by the lexical analyzer during single pass of the source code.
The token name corresponding to the current node is printed third. If the lexeme is an integer or real number,
then its value computed by the lexical analyzer should be printed at the fourth place. Print the grammar symbol
(non-terminal symbol) of the parent node of the currently visited node appropriately at fifth place
(for the root node print ROOT for parent symbol) . The sixth column is for printing yes or no appropriately.
Print the non-terminal symbol of the node being currently visited at the 7th place, if the node is not the leaf node
[Print the actual non-terminal symbol and not the enumerated values for the non-terminal].
Ensure appropriate justification so that the columns appear neat and straight.*/

Parser init_parser(char *lexer_filename, char *grammar_filename)
{
    Parser parser = (Parser)malloc(sizeof(struct parser));
    parser->currentNode = NULL;
    parser->position = 0;
    parser->lexer = init_lexer(lexer_filename);
    parser->grammar = init_grammar(grammar_filename);
    parser->noError = true;

    parser->stack = init_vector(TOKEN);
    Token eo_stack = init_token(EO_STACK, char_to_string("$"), "S", -1, -1);
    push_back(parser->stack, eo_stack);

    return parser;
}

bool isKeywordSynToken(String string)
{
    for (int i = 0; i < 14; i++) // NOTE: length hard-coded
    {
        String fromList = char_to_string(keyword_syn_token_list[i]);
        if (compare(string, fromList))
            return true;
    }
    return false;
}

void _panicRecovery()
{
}

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
    char error_msg[200];
    SymbolTable symbolTable = init_table();
    Parser parser = init_parser(testcaseFile, "grammar.txt");

    populateFirst(parser->grammar);
    populateFollow(parser->grammar);
    populateParseTable(parser->grammar);

    // printParseTable(parser->grammar);

    Vector parseTable = parser->grammar->parseTable;

    Rule start_symbol = get(parser->grammar->rules, 0);

    // Pushing start symbol of the grammar into the stack
    TreeNode tree = init_treenode(start_symbol->NT);
    tokenToChildren(tree, start_symbol->derivables);

    TreeNode currentParent = tree;
    push_back(parser->stack, start_symbol->NT);
    // printVector(parser->stack);
    parser->currentNode = getNextToken(parser->lexer);
    Token top_of_stack = (Token)top(parser->stack);

    // return tree;

    while (top_of_stack->type != EO_STACK)
    {
        printf("current: %s, type: %s\n", parser->currentNode->lexeme_str->text, token_type_list[parser->currentNode->type]);
        printf("STACK: ");
        printVector(parser->stack);
        printf("\n\n");
        if (compare(char_to_string(token_type_list[parser->currentNode->type]), top_of_stack->lexeme_str))
        {
            updateTerminalInTree(tree, parser->currentNode);
            insert_item(symbolTable, parser->currentNode->lexeme_str, parser->currentNode);
            pop_back(parser->stack);

            // printf(" before match- current: %s, type: %s\n", parser->currentNode->lexeme_str->text, token_type_list[parser->currentNode->type]);
            // if(parser->lexer->BUFF_NUM==1){
            //     printf("%s\n", parser->lexer->buff1[parser->lexer->fwd_ptr]);
            // }
            // else
            //     printf("%s\n", parser->lexer->buff2[parser->lexer->fwd_ptr]);
            parser->currentNode = getNextToken(parser->lexer);
            // printf(" after match- current: %s, type: %s\n", parser->currentNode->lexeme_str->text, token_type_list[parser->currentNode->type]);
        }
        else // error-recovery
        {
            if (top_of_stack->type == TERMINAL)
            {
                // char error_msg[200];
                if (parser->currentNode->type == TK_ILLEGAL) //  lexical errors
                {
                    // info("Error recovery invoked. Lexical error");
                    char *error_msg_tk = parser->currentNode->error_msg;
                    sprintf(error_msg, "Line %2d Error: %s", parser->currentNode->line_num, error_msg_tk);
                    // while (parser->currentNode->type == TK_ILLEGAL)
                    // printf("2 before match- current: %s, type: %s\n", parser->currentNode->lexeme_str->text, token_type_list[parser->currentNode->type]);
                    parser->currentNode = getNextToken(parser->lexer);
                    // printf("2 after match- current: %s, type: %s\n", parser->currentNode->lexeme_str->text, token_type_list[parser->currentNode->type]);

                    error(error_msg);
                }

                char err_terminal[100];
                sprintf(err_terminal, "Line %2d Error: The token %s for lexeme %s  does not match with the expected token %s",
                        parser->currentNode->line_num,
                        token_type_list[parser->currentNode->type],
                        parser->currentNode->lexeme_str->text,
                        top_of_stack->lexeme_str->text);
                error(err_terminal);
                pop_back(parser->stack);
                top_of_stack = top(parser->stack);
                continue;
            }
            Vector tableRow = (Vector)get(parseTable, top_of_stack->type);

            Rule rule = (Rule)get(tableRow, parser->currentNode->type);

            if (parser->currentNode->type == TK_ILLEGAL || rule->NT->type == SYN || rule->NT->type == ERROR)
            {
                // error recovery mechanism: Panic-Mode Recovery
                /*If the parser looks up entry M[A,a] and finds that it is blank/error, the input symbol a is skipped.
                    If the entry is syn, then the nonterminal on top of the stack is popped.*/

                printf("error lexeme: %s, type: %s line: %d \n", parser->currentNode->lexeme_str->text, token_type_list[parser->currentNode->type], parser->currentNode->line_num);
                if (parser->currentNode->type == TK_ILLEGAL) //  lexical errors
                {
                    info("Error recovery invoked. Lexical error");
                    char *error_msg = parser->currentNode->error_msg;
                    error(error_msg);
                    // while (parser->currentNode->type == TK_ILLEGAL)
                    parser->currentNode = getNextToken(parser->lexer);
                }
                else if (rule->NT->type == ERROR) // error entry in parse table
                {
                    info("Error recovery invoked. ERROR entry");
                    error("syntactical error");

                    if (isKeywordSynToken(char_to_string(token_type_list[parser->currentNode->type])))
                        parser->currentNode = getNextToken(parser->lexer);

                    char *prev_sync;
                    while (!isKeywordSynToken(char_to_string(token_type_list[parser->currentNode->type])) && (rule->NT->type != SYN) && (rule->NT->type != FIRST_SYN)) // special keyword check
                    {
                        // printf("4 before match- current: %s, type: %s\n", parser->currentNode->lexeme_str->text, token_type_list[parser->currentNode->type]);
                        prev_sync = parser->currentNode->lexeme_str->text;
                        parser->currentNode = getNextToken(parser->lexer);
                        // printf("4 after match- current: %s, type: %s\n", parser->currentNode->lexeme_str->text, token_type_list[parser->currentNode->type]);
                        rule = (Rule)get(tableRow, parser->currentNode->type);
                        printf("lexeme: %s, type: %s line: %ld ",
                               parser->currentNode->lexeme_str->text,
                               token_type_list[parser->currentNode->type],
                               parser->currentNode->line_num);

                        printf("---bool: %d \n", isKeywordSynToken(char_to_string(token_type_list[parser->currentNode->type])));
                    }
                    // while (rule->NT->type == SYN || isKeywordSynToken(char_to_string(token_type_list[parser->currentNode->type])))
                    // {
                    //     pop_back(parser->stack);
                    //     top_of_stack = top(parser->stack);
                    //     if(top_of_stack->type==TERMINAL) break;
                    //     tableRow = (Vector)get(parseTable, top_of_stack->type);
                    //     rule = (Rule)get(tableRow, parser->currentNode->type);
                    // }
                    info("Error recovery invoked. SYN(follow set)");
                    sprintf(error_msg, "Line %2d Error: Invalid token %s encountered with value %s stack top %s",
                            parser->currentNode->line_num,
                            token_type_list[parser->currentNode->type],
                            parser->currentNode->lexeme_str->text,
                            top_of_stack->lexeme_str->text);
                    error(error_msg);
                    // continue;
                    if (rule->NT->type != FIRST_SYN)
                    {
                        pop_back(parser->stack);
                        // top_of_stack = top(parser->stack);
                    }
                    // if (isKeywordSynToken(char_to_string(token_type_list[parser->currentNode->type])))
                    //     parser->currentNode = getNextToken(parser->lexer);
                }
                else if (rule->NT->type == SYN)
                {
                    pop_back(parser->stack);
                    info("Error recovery invoked. SYN(follow set)");
                    // char error_msg[200];
                    sprintf(error_msg, "Line %2d Error: Invalid token %s encountered with value %s stack top %s",
                            parser->currentNode->line_num,
                            token_type_list[parser->currentNode->type],
                            parser->currentNode->lexeme_str->text,
                            top_of_stack->lexeme_str->text);
                    error(error_msg);
                    top_of_stack = top(parser->stack);
                    // continue;
                }
            }
            else if (rule)
            {
                printRule(rule);
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

    printf("\nPARSE TREE \n");
    saveParseTree(tree, 0);
    printSymbolTable(symbolTable);
    // prettyPrintParseTree(tree);
    return tree;
}
