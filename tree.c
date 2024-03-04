/*
Group Number: 28
1. Anishka Singh 2020B3A70816P
2. Gautam Jajoo 2020B3A71638P
3. Suraj Phalod 2020B3A71959P
4. Ria Shekhawat 2020B4A71986P
5. Karan Agrawal 2020B4A70830P
*/
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

void updateTerminalInTree(TreeNode root, Token token)
{

    if (compare(char_to_string(token_type_list[token->type]), root->value->lexeme_str))
    {
        if (root->value->line_num == 0)
        {
            // root->value = copy_token(root->value, token);
            root->value->lexeme_value = token->lexeme_str->text;
            root->value->line_num = token->line_num;
            root->value->char_num = token->char_num;
            return;
        }
    }

    for (int i = 0; i < root->children->size; i++)
    {
        updateTerminalInTree((TreeNode)get(root->children, i), token);
    }
}

void printTree(FILE *fp, TreeNode root, int level)
{
    if (root->children->size > 0)
        printTree(fp, (TreeNode)get(root->children, 0), level + 1);

    // lexeme CurrentNode lineno tokenName valueIfNumber parentNodeSymbol isLeafNode(yes / no) NodeSymbol
    int lineno;
    double valueIfNumber = -1;
    char *lexeme = malloc(100);
    char *CurrentNode = malloc(100);
    char *tokenName = malloc(100);
    char *parentNodeSymbol = malloc(100);
    char *isLeafNode = malloc(4);
    char *NodeSymbol = malloc(100);

    CurrentNode = root->value->lexeme_str->text;
    NodeSymbol = CurrentNode;
    if (!root->parent)
        parentNodeSymbol = "ROOT";
    else
        parentNodeSymbol = root->parent->value->lexeme_str->text;
    if (root->children->size == 0)
    {
        isLeafNode = "yes";
        lexeme = root->value->lexeme_value;
        tokenName = CurrentNode;
    }
    else
    {
        isLeafNode = "no";
        lexeme = "-----";
        tokenName = "-----";
    }

    lineno = root->value->line_num;
    if (compare(root->value->lexeme_str, char_to_string("TK_NUM")) || compare(root->value->lexeme_str, char_to_string("TK_RNUM")))
        valueIfNumber = *(double *)(root->value->lexeme_value);

    fprintf(fp, "Lexeme:%13s CurrentNode:%25s Line no.:%3d  tokenName:%13s valueIfNumber:%.3f parentNodeSymbol:%25s isLeafNode:%4s NodeSymbol:%25s \n", lexeme, CurrentNode, lineno,
            tokenName, valueIfNumber, parentNodeSymbol, isLeafNode, NodeSymbol);

    for (int i = 1; i < root->children->size; i++)
    {
        printTree(fp, (TreeNode)get(root->children, i), level + 1); // Traverse rest of the subtrees
    }
}

void saveParseTree(TreeNode root, int level, char *treefile)
{
    FILE *fp = fopen(treefile, "w+");
    printTree(fp, root, 0);
    fclose(fp);
    char treeAffirm[100];
    sprintf(treeAffirm, "Parse tree generated and saved in &s.", treefile);
        info(treeAffirm);
}