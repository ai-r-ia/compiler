/*
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/
#ifndef TREEDEF
#define TREEDEF
#include "lexical_token.h"
#include "vectors.h"
#include "rules.h"

// struct for parse tree
typedef struct treeNode *TreeNode;

struct treeNode
{
    Token value;
    Vector children;
    TreeNode parent;

} extern treeNode;

#endif