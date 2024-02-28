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

void addToTree(TreeNode parent, Rule rule)
{
    bool addedNodes = false;

    Vector rhs = init_vector(TOKEN);
    rhs = rule->derivables;
    Token nonTerminal = rule->NT;
    for (int i = 0; i < parent->children->size; i++)
    {
        TreeNode child = (TreeNode)get(parent->children, i);
        if ((child->value->type == nonTerminal->type) && child->children->size == 0)
        {
            tokenToChildren(child, rhs);
            addedNodes = true;
            // return child;
        }
    }

    if (!addedNodes)
    {
        for (int i = 0; i < parent->children->size; i++)
        {
            addToTree((TreeNode)get(parent->children, i), rule);
        }
    }
    // return parent;
}

void printTree(TreeNode root, int level)
{
    // lexeme CurrentNode lineno tokenName valueIfNumber parentNodeSymbol isLeafNode(yes / no) NodeSymbol
    int lineno;
    double valueIfNumber = -1;
    char *lexeme = malloc(100);
    char *CurrentNode = malloc(100);
    char *tokenName = malloc(100);
    char *parentNodeSymbol = malloc(100);
    char *isLeafNode = malloc(4);
    char *NodeSymbol = malloc(100);
    CurrentNode = token_type_list[root->value->type]; // NOTE: vs tokenName ....symboltable
    tokenName = token_type_list[root->value->type];   // NOTE: vs tokenName ....symboltable
    if (!root->parent)
        parentNodeSymbol = "ROOT";
    else
        parentNodeSymbol = token_type_list[root->parent->value->type];
    if (root->children->size == 0)
    {
        isLeafNode = "yes";
        lexeme = root->value->lexeme_str->text;
    }
    else
    {
        isLeafNode = "no";
        lexeme = "-----";
    }

    NodeSymbol = token_type_list[root->value->type]; // NOTE: vs tokenName ....symboltable

    lineno = root->value->line_num;
    if (compare(root->value->lexeme_str, char_to_string("TK_NUM")) || compare(root->value->lexeme_str, char_to_string("TK_RNUM")))
        valueIfNumber = *(double *)(root->value->lexeme_value);

    for (int i = 0; i < root->children->size / 2; i++)
    {
        printTree((TreeNode)get(root->children, i), level + 1);
    }
    // printf("%s      ---%d\n", root->value->lexeme_str->text, level);
    printf("Lexeme: %15s CurrentNode: %15s Line no.: %3d  tokenName: %s valueIfNumber: %.3f parentNodeSymbol: %15s isLeafNode: %s NodeSymbol: %15s lvl:%3d\n", lexeme, CurrentNode, lineno,
           tokenName, valueIfNumber, parentNodeSymbol, isLeafNode, NodeSymbol, level);
    for (int i = root->children->size / 2; i > 0; i--)
    {
        printTree((TreeNode)get(root->children, i), level + 1);
    }
    // printf("\n");
}

// Tree init_tree(Token rootValue){
//     Tree tree = (Tree)malloc(sizeof(struct tree));
//     tree->root = init_treenode(rootValue);
// }
