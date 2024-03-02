#ifndef PARSER
#define PARSER

// #include "whole_include.h"
#include "tree.h"
#include "parserDef.h"
// #include "treeDef.h"

bool isKeywordSynToken(String string);

Parser init_parser(char *filename, char *grammar);

TreeNode parseInputSourceCode(char *testcaseFile);

#endif