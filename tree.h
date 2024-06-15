/* 
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/ 
#ifndef TREE
#define TREE
#include "treeDef.h"
#include "printers.h"
#include "lexer.h"

TreeNode init_treenode(Token value);

void addChild(TreeNode node, Token token);

void tokenToChildren(TreeNode parent, Vector tokens);

void addToTree(TreeNode parent, Rule rule);

void updateTerminalInTree(TreeNode root, Token token);

void printTree(FILE *fp, TreeNode root, int level);

void saveParseTree(TreeNode root, int level, char* treefile);
#endif