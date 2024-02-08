#include "whole_include.h"

// initialize symbol_node
SymbolNode init_symbol(String lexeme, Token token)
{
    SymbolNode symnode = (SymbolNode)malloc(sizeof(symbol_node));
    symnode->lexeme = lexeme;
    symnode->token = token;

    return symnode;
}

// insert entry into symbol table
void insert(Vector vec, String lexeme, Token token){
    SymbolNode symnode = init_symbol(lexeme, token);
    push_back(vec, symnode);
}

// lookup
SymbolNode search(String lexeme);