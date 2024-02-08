#include "whole_include.h"

// initialize symbol_node
void init_symbol(String lexeme, Token token);

// initialize symbol_node
void init_symbol_table();

// insert entry into symbol table
void insert(String lexeme, Token token);

// lookup
SymbolNode search(String lexeme);