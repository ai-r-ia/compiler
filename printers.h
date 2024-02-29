#ifndef PRINTERS
#define PRINTERS
#define WHITE "\x1B[0m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
#define RED "\033[0;31m"
#define traceback(...)                             \
    do                                             \
    {                                              \
        printf("@ %s (%d): ", __FILE__, __LINE__); \
        printf(__VA_ARGS__);                       \
    } while (0)

#include "tree.h"

void debug(char *message);
void error(char *message);
void info(char *message);
void success(char *message);
void prettyPrintParseTree(TreeNode node);
void _prettyPrintParseTree(TreeNode node, int level);
// void prettyPrintParseTreeF(TreeNode node, FILE *fp);
// void _prettyPrintParseTreeF(TreeNode node, int level, FILE *fp);
void prettyPrintAST(TreeNode node);
#endif