#ifndef PARSER
#define PARSER

// #include "whole_include.h"
#include "tree.h"
// #include "treeDef.h"
#include "parserDef.h"

///
// void setGrammar(Parser parser, char *fileName);

// Token nextToken(Parser parser);

// Token getCurrent(Parser parser);

// Token peek(Parser parser, size_t offset);

// void runLexer(Parser parser);

// Token match(Parser parser, int kind);

// TreeNode parseExpression(Parser parser, int parentPrecedence);

// TreeNode parserPrimaryExpression(Parser parser);

// TreeNode nextParseTree(Parser parser);

// private functions

// void _parse(Parser parser, TreeNode node);

// defined functions

Parser init_parser(char *filename, char *grammar);

TreeNode parseInputSourceCode(char *testcaseFile);

#endif