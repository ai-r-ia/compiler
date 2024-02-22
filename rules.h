#ifndef RULES
#define RULES

#include "lexical_token.h"
#include "vectors.h"
#include "stdio.h"

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
    singleOrRecId,
    constructedVariable,
    funCallStmt,
    outputParameters,
    inputParameters,
    iterativeStmt,
    conditionalStmt,
    elsePart,
    ioStmt,
    arithmeticExpression,
    expPrime,
    term,
    termPrime,
    factor,
    highPrecedenceOperators,
    lowPrecedenceOperators,
    booleanExpression,
    var,
    logicalOp,
    relationalOp,
    returnStmt,
    optionalReturn,
    idList,
    more_ids,
    definetypestmt,
    actualOrRedefined,
    option_single_constructed,
    oneExpansion,
    moreExpansions,
    A,

    // Do not belong to non terminals
    TERMINAL,
    INVALID_GTOK,
    EO_STACK
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
        "singleOrRecId",
        "constructedVariable",
        "funCallStmt",
        "outputParameters",
        "inputParameters",
        "iterativeStmt",
        "conditionalStmt",
        "elsePart",
        "ioStmt",
        "arithmeticExpression",
        "expPrime",
        "term",
        "termPrime",
        "factor",
        "highPrecedenceOperators",
        "lowPrecedenceOperators",
        "booleanExpression",
        "var",
        "logicalOp",
        "relationalOp",
        "returnStmt",
        "optionalReturn",
        "idList",
        "more_ids",
        "definetypestmt",
        "actualOrRedefined",
        "option_single_constructed",
        "oneExpansion",
        "moreExpansions",
        "A",

        // Not non terminals
        "Terminal",
        "INVALID_GTOK",
        "$"};

typedef struct grammar *Grammar;
struct grammar
{
    char *filename;
    Vector rules;
    Vector first;
    Vector follow;
    int *nullable;
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

void populateFirst(Grammar grammar);

void populateFollow(Grammar grammar);

Vector getFirst(Token token, Grammar grammar);

Vector getFollow(Token token, Grammar grammar);

// private functions

void _loadGrammar(Grammar grammar);

int _matchNonTerminal(String nonTerminal);

#endif