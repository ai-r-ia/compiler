#ifndef TREEDEF
#define TREEDEF
#include "lexical_token.h"
#include "vectors.h"
#include "rules.h"

typedef struct treeNode *TreeNode;

struct treeNode
{
    Token value;
    Vector children;
    // TreeNode rightchild, leftchild;
    TreeNode parent;

} treeNode;

typedef struct tree *Tree;
struct tree
{
    TreeNode root;
    // Token token;

} tree;

#endif