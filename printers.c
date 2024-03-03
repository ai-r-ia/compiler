/* 
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/ 
#include "printers.h"
#include "whole_include.h"
void debug(char *message) { printf("%sDebug:- %s %s\n", WHITE, message, WHITE); }
void error(char *message) { printf("%s%s %s\n", RED, message, WHITE); }
void info(char *message) { printf("%sinfo:- %s %s\n", BLUE, message, WHITE); }
void success(char *message) { printf("%sSuccess:- %s %s\n", GREEN, message, WHITE); }

void prettyPrintParseTree(TreeNode node)
{
    printf("-- Parse Tree --\n");
    _prettyPrintParseTree(node, 0);
}

void _prettyPrintParseTree(TreeNode node, int level)
{
    if (node == NULL || node->value == NULL)
        return;

    for (int i = 0; i < level; i++)
        printf("|--");

    if (node->value->type == TERMINAL)
    {
        if (node->value->lexeme_str == NULL)
            printf("Expected: %s\n", token_type_list[node->value->type]);
        else
            printf("%s\n", node->value->lexeme_str->text);
    }
    else
    {
        if (node->value->lexeme_str == NULL)
            printf("Expected: %s\n", grammarTokenKindString[node->value->type]);
        else
            printf("%s\n", grammarTokenKindString[node->value->type]);
    }
    if (node->children == NULL)
        return;
    for (size_t i = 0; i < (node->children->size); i++)
    {
        _prettyPrintParseTree((TreeNode)get(node->children, i), level + 1);
    }
}

// void prettyPrintParseTreeF(TreeNode  node, FILE *fp)
// {
//     printf("-- Parse Tree (Pre order Traversal) --\n\n");
//     _prettyPrintParseTreeT(node, NULL, 0);
//     // printf("\n\n\n-- Parse Tree in Tree format --\n\n");
//     // _prettyPrintParseTree(node, 0);
//     fp = fopen("./parser-tree-output.txt", "w+");
//     fprintf(fp, "-- Parse Tree (Pre order Traversal) --\n\n");
//     _prettyPrintParseTreeFT(node, NULL, 0, fp);
//     fprintf(fp, "\n\n\n-- Parse Tree in Tree format --\n\n");
//     _prettyPrintParseTreeF(node, 0, fp);
//     fclose(fp);
// }

// void _prettyPrintParseTreeF(TreeNode  node, int level, FILE *fp)
// {
//     if (node == NULL || node->value == NULL)
//         return;

//     for (int i = 0; i < level; i++)
//         fprintf(fp, "|--");

//     if (node->value->type  == TERMINAL)
//     {
//         if (node->value->lexeme_str == NULL)
//             fprintf(fp, "Expected: %s\n", token_type_list[node->value->type]);
//         else
//             fprintf(fp, "%s\n", node->value->lexeme_str->text);
//     }
//     else
//     {
//         if (node->value->lexeme_str == NULL)
//             fprintf(fp, "Expected: %s\n", grammarTokenKindString[node->value->type ]);
//         else
//             fprintf(fp, "%s\n", grammarTokenKindString[node->value->type ]);
//     }

//     for (size_t i = 0; i < (node->children->size); i++)
//     {
//         _prettyPrintParseTreeF((TreeNode  )get(node->children, i), level + 1, fp);
//     }
// }

void prettyPrintAST(TreeNode node)
{
    // printf("-- AST (Pre order Traversal) --\n\n");
    // _prettyPrintParseTreeT(node, NULL, 0);
    printf("\n\n\n-- AST in Tree format --\n\n");
    _prettyPrintParseTree(node, 0);

    // FILE *fp = fopen("./ast-output.txt", "w+");
    // // fprintf(fp, "-- AST (Pre order Traversal) --\n\n");
    // // _prettyPrintParseTreeFT(node, NULL, 0, fp);
    // // fprintf(fp, "\n\n\n-- AST in Tree format --\n\n");
    // // _prettyPrintParseTreeF(node, 0, fp);
    // fclose(fp);
}