#ifndef TREE
#define TREE
#include "treeDef.h"
#include "printers.h"
#include "lexer.h"

TreeNode init_treenode(Token value);

// TreeNode copy_node(TreeNode destination, TreeNode source);

// Tree init_tree(Token rootValue);

void addChild(TreeNode node, Token token);

void tokenToChildren(TreeNode parent, Vector tokens);

void addToTree(TreeNode parent, Rule rule);

void updateTerminalInTree(TreeNode root, Token token);

void printTree(FILE *fp, TreeNode root, int level);

void saveParseTree(TreeNode root, int level);
#endif