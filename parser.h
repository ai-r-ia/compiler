#ifndef PARSER
#define PARSER

// #include "whole_include.h"
#include "tree.h"
#include "parserDef.h"
// #include "treeDef.h"

bool isKeywordSynToken(String string);

bool isStartKeyword(String string);

Parser init_parser(char *filename);

TreeNode parseInputSourceCode(char *testcaseFile, char *treefile);

#endif