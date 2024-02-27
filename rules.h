#ifndef RULES
#define RULES

#include "lexical_token.h"
#include "vectors.h"
#include "stdio.h"
#include "vectorDef.h"

#define GRAMMAR_LENGTH 10000

enum GrammarTokenKind
{
    program,
    mainFunction,
    otherFunctions,
    function,
    input_par,
    output_par,
    parameter_list,
    dataType,
    primitiveDatatype,
    constructedDatatype,
    remaining_list,
    stmts,
    typeDefinitions,
    actualOrRedefined,
    typeDefinition,
    fieldDefinitions,
    fieldDefinition,
    fieldtype,
    moreFields,
    declarations,
    declaration,
    global_or_not,
    otherStmts,
    stmt,
    assignmentStmt,
    arithmeticExpression,
    expPrime,
    term,
    termPrime,
    factor,
    var,
    singleOrRecId,
    option_single_constructed,
    oneExpansion,
    moreExpansions,
    funCallStmt,
    outputParameters,
    inputParameters,
    iterativeStmt,
    conditionalStmt,
    elsePart,
    ioStmt,
    highPrecedenceOperators,
    lowPrecedenceOperators,
    booleanExpression,
    logicalOp,
    relationalOp,
    returnStmt,
    optionalReturn,
    idList,
    more_ids,
    definetypestmt,
    A,

    // Do not belong to non terminals
    TERMINAL,
    INVALID_GTOK,
    EO_STACK,
    SYN,
};

static char *grammarTokenKindString[] =
    {
        "program",
        "mainFunction",
        "otherFunctions",
        "function",
        "input_par",
        "output_par",
        "parameter_list",
        "dataType",
        "primitiveDatatype",
        "constructedDatatype",
        "remaining_list",
        "stmts",
        "typeDefinitions",
        "actualOrRedefined",
        "typeDefinition",
        "fieldDefinitions",
        "fieldDefinition",
        "fieldtype",
        "moreFields",
        "declarations",
        "declaration",
        "global_or_not",
        "otherStmts",
        "stmt",
        "assignmentStmt",
        "arithmeticExpression",
        "expPrime",
        "term",
        "termPrime",
        "factor",
        "var",
        "singleOrRecId",
        "option_single_constructed",
        "oneExpansion",
        "moreExpansions",
        "funCallStmt",
        "outputParameters",
        "inputParameters",
        "iterativeStmt",
        "conditionalStmt",
        "elsePart",
        "ioStmt",
        "highPrecedenceOperators",
        "lowPrecedenceOperators",
        "booleanExpression",
        "logicalOp",
        "relationalOp",
        "returnStmt",
        "optionalReturn",
        "idList",
        "more_ids",
        "definetypestmt",
        "A",

        // Not non terminals
        "Terminal",
        "INVALID_GTOK",
        "$",
        "SYN",
};

typedef struct grammar *Grammar;
struct grammar
{
    char *filename;
    Vector rules;
    Vector first;
    Vector follow;
    int *nullable;
    Vector parseTable;
} grammar;

typedef struct rule *Rule;
struct rule
{
    Token NT;          // non terminal
    Vector derivables; // rhs of rule
} rule;

Rule init_rule(Token NT);

Grammar init_grammar(char *filename);

void printRule(Rule rule);

void printParseTable(Grammar grammar);

void populateFirst(Grammar grammar);

void populateFollow(Grammar grammar);

void populateParseTable(Grammar grammar);

Vector getFirst(Token token, Grammar grammar);

// private functions

void _loadGrammar(Grammar grammar);

int _matchNonTerminal(String nonTerminal);

#endif