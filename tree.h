#ifndef TREE
#define TREE
#include "treeDef.h"

TreeNode init_treenode(Token value);

// TreeNode copy_node(TreeNode destination, TreeNode source);

// Tree init_tree(Token rootValue);

void addChild(TreeNode node, Token token);

void tokenToChildren(TreeNode parent, Vector tokens);

TreeNode addToTree(TreeNode parent, Rule rule);

void printTree(TreeNode root);
#endif