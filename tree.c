#include "tree.h"
#include <stdlib.h>

TreeNode init_treenode(Token value)
{
    TreeNode tnode = (TreeNode)malloc(sizeof(struct treeNode));
    tnode->value = value;
    tnode->children = init_vector(TREENODE);
    tnode->parent = NULL;
}

void addChild(TreeNode node, Token token)
{
    TreeNode child = init_treenode(token);
    child->parent = node;
    push_back(node->children, child);
}

void tokenToChildren(TreeNode parent, Vector tokens)
{
    for (int i = 0; i < tokens->size; i++)
    {
        addChild(parent, get(tokens, i));
    }
}

TreeNode addToTree(TreeNode parent, Rule rule)
{
    Vector rhs = init_vector(TOKEN);
    rhs = rule->derivables;
    Token nonTerminal = rule->NT;
    for (int i = 0; i < parent->children->size; i++)
    {
        TreeNode child = (TreeNode)get(parent->children, i);
        if (child->value->type == nonTerminal->type)
        {
            tokenToChildren(child, rhs);
            return child;
        }
    }
    return parent;
}

void printTree(TreeNode root)
{
    printf("%s--", root->value->lexeme_str->text);
    for (int i = 0; i < root->children->size; i++)
    {
        printTree((TreeNode)get(root->children, i));
    }
    printf("\n");
}

// Tree init_tree(Token rootValue){
//     Tree tree = (Tree)malloc(sizeof(struct tree));
//     tree->root = init_treenode(rootValue);
// }
