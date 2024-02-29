#include <stdlib.h>
#include "parser.h"
#include "printers.h"

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
    Parser parser = init_parser(testcaseFile, "grammar.txt");

    populateFirst(parser->grammar);
    populateFollow(parser->grammar);
    populateParseTable(parser->grammar);

    // printParseTable(parser->grammar);

    Vector parseTable = parser->grammar->parseTable;

    Rule start_symbol = get(parser->grammar->rules, 0);

    // Pushing start symbol of our grammar in stack
    TreeNode tree = init_treenode(start_symbol->NT);
    tokenToChildren(tree, start_symbol->derivables);

    TreeNode currentParent = tree;
    push_back(parser->stack, start_symbol->NT);
    // printVector(parser->stack);
    parser->currentNode = getNextToken(parser->lexer);
    Token top_of_stack = (Token)top(parser->stack);

    while (top_of_stack->type != EO_STACK)
    {
        printf("STACK: ");
        printVector(parser->stack);
        printf("\n");
        if (compare(char_to_string(token_type_list[parser->currentNode->type]), top_of_stack->lexeme_str))
        {
            updateTerminalInTree(tree, parser->currentNode);
            pop_back(parser->stack);
            parser->currentNode = getNextToken(parser->lexer);
        }
        else
        {
            printf("current: %s \n", parser->currentNode->lexeme_str->text);
            if (top_of_stack->type == TERMINAL)
            {
                char err_terminal[100];
                sprintf(err_terminal, "Terminal %s popped from stack.", top_of_stack->lexeme_str->text);
                error(err_terminal);
                pop_back(parser->stack);
                top_of_stack = top(parser->stack);
                continue;
            }
            Vector tableRow = (Vector)get(parseTable, top_of_stack->type);

            Rule rule = (Rule)get(tableRow, parser->currentNode->type);

            if (rule->NT->type == TK_ILLEGAL || rule->NT->type == SYN)
            {
                error("Error recovery invoked.");
                // error recovery mechanism: Panic-Mode Recovery
                /*If the parser looks up entry M[A,a] and finds that it is blank/error, the input symbol a is skipped.
                    If the entry is syn, then the nonterminal on top of the stack is popped.*/

                if (rule->NT->type == TK_ILLEGAL)
                    parser->currentNode = getNextToken(parser->lexer);
                else if (rule->NT->type == SYN)
                    pop_back(parser->stack);
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
    // printTree(tree, 0);
    saveParseTree(tree,0);
        // prettyPrintParseTree(tree);
        return tree;
}
